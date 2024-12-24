#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "game.h"
#include "strategy.h"

enum class GameMode {
    DEFAULT_MODE,
    DETAILED_MODE,
    FAST_MODE,
    TOURNAMENT_MODE,
};

struct Arguments {
    GameMode mode = GameMode::DEFAULT_MODE;
    int steps = 0;
    std::string config_dir;
    std::string matrix_file;
};

void usage() {
    std::cout << "Usage: lab2a [options] strategy1 strategy2 strategy3 ..."
              << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --mode=MODE" << std::endl;
    std::cout << "    Game mode" << std::endl;
    std::cout << "    Available modes: detailed, fast, tournament" << std::endl;
    std::cout << "  --steps=NUMBER" << std::endl;
    std::cout << "    Number of steps" << std::endl;
    std::cout << "    Default: 10. Must be > 0 and <= 100" << std::endl;
    std::cout << "  --config-dir=PATH" << std::endl;
    std::cout << "    Path to strategies config directory" << std::endl;
    std::cout << "  --matrix=PATH" << std::endl;
    std::cout << "    Path to payoff matrix file" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Available strategies:" << std::endl;
    for (const auto &strategy_name : StrategyFactory::getAllStrategies()) {
        std::cout << "    " << strategy_name << std::endl;
    }
}

static std::unique_ptr<Arguments>
parse_arguments(int argc, char *argv[], std::vector<std::string> &strategies) {
    auto args = std::make_unique<Arguments>();
    for (int i = 1; i < argc; i++) {
        const std::string curr = argv[i];
        if (curr.starts_with("--")) {
            // Possible argument
            if (curr.starts_with("--mode=")) {
                if (args->mode != GameMode::DEFAULT_MODE) {
                    throw std::invalid_argument("Mode already set");
                }

                const std::string mode_name = curr.substr(7);
                if (mode_name == "detailed") {
                    args->mode = GameMode::DETAILED_MODE;
                } else if (mode_name == "fast") {
                    args->mode = GameMode::FAST_MODE;
                } else if (mode_name == "tournament") {
                    args->mode = GameMode::TOURNAMENT_MODE;
                } else {
                    throw std::invalid_argument("Unknown mode: " + curr);
                }
            } else if (curr.starts_with("--steps=")) {
                if (args->steps != 0) {
                    throw std::invalid_argument("Steps already set");
                }

                const auto steps = std::stoull(curr.substr(8));
                if (steps < 1 || steps > 100) {
                    throw std::invalid_argument("Wrong number of steps: " +
                                                std::to_string(steps));
                }
                args->steps = steps;
            } else if (curr.starts_with("--configs=")) {
                if (!args->config_dir.empty()) {
                    throw std::invalid_argument("Config dir already set");
                }

                const std::string config_dir = curr.substr(10);
                args->config_dir = config_dir;
            } else if (curr.starts_with("--matrix=")) {
                if (!args->matrix_file.empty()) {
                    throw std::invalid_argument("Matrix file already set");
                }

                const std::string matrix_file = curr.substr(9);
                args->matrix_file = matrix_file;
            } else if (curr.starts_with("--help")) {
                usage();
                exit(EXIT_SUCCESS);
            } else {
                throw std::invalid_argument("Unknown argument: " + curr);
            }
        } else {
            // Parse strategies
            strategies.push_back(curr);
        }
    }

    // Check required args
    if (strategies.size() < 3) {
        throw std::invalid_argument("Not enough strategies specified");
    }
    if (args->mode == GameMode::FAST_MODE && strategies.size() != 3) {
        throw std::invalid_argument("Fast mode requires exactly 3 strategies");
    }

    // Set defaults
    if (args->steps == 0) {
        args->steps = 10;
    }
    if (args->mode == GameMode::DEFAULT_MODE) {
        args->mode = strategies.size() == 3 ? GameMode::DETAILED_MODE
                                            : GameMode::TOURNAMENT_MODE;
    }
    return args;
}

static std::array<std::array<int, 3>, 8> default_matrix = {
    std::array{1, 1, 1}, std::array{5, 5, 0}, std::array{5, 0, 5},
    std::array{9, 3, 3}, std::array{0, 5, 5}, std::array{3, 9, 3},
    std::array{3, 3, 9}, std::array{7, 7, 7}};

static std::array<std::array<int, 3>, 8>
load_matrix(const std::string &filename) {
    std::array<std::array<int, 3>, 8> matrix;
    std::ifstream file(filename);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 3; j++) {
            file >> matrix[i][j];
        }
    }
    return matrix;
}

int main(int argc, char *argv[]) {
    std::set_terminate([]() {
        try {
            std::exception_ptr eptr{std::current_exception()};
            if (eptr) {
                std::rethrow_exception(eptr);
            } else {
                std::cerr << "Exiting without exception" << std::endl;
            }
        } catch (const std::exception &ex) {
            std::cerr << "Error: " << std::endl;
            std::cerr << ex.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown exception caught" << std::endl;
        }
        std::exit(EXIT_FAILURE);
    });

    std::vector<std::string> strategies_names;
    auto arguments = parse_arguments(argc, argv, strategies_names);

    auto matrix = arguments->matrix_file.empty()
                      ? default_matrix
                      : load_matrix(arguments->matrix_file);

    std::vector<std::shared_ptr<Strategy>> strategies;
    for (const auto &strategy_name : strategies_names) {
        strategies.push_back(StrategyFactory::createStrategy(
            strategy_name, arguments->config_dir, matrix));
    }
    std::vector<int> results(strategies.size(), 0);

    if (arguments->mode == GameMode::FAST_MODE) {
        Game game(strategies[0], strategies[1], strategies[2], matrix);
        for (int i = 0; i < arguments->steps; i++) {
            game.playRound();
        }
        game.printResults();
        return EXIT_SUCCESS;
    }

    for (size_t a = 0; a < strategies.size() - 2; a++) {
        for (size_t b = a + 1; b < strategies.size() - 1; b++) {
            for (size_t c = b + 1; c < strategies.size(); c++) {
                if (a == b || a == c || b == c) {
                    continue;
                }

                std::cout << "GAME: " << strategies[a]->getName() << " : "
                          << strategies[b]->getName() << " : "
                          << strategies[c]->getName() << std::endl;

                Game game(strategies[a], strategies[b], strategies[c], matrix);
                for (int i = 0; i < arguments->steps; i++) {
                    auto [r_a, r_b, r_c] = game.playRound();
                    if (arguments->mode == GameMode::DETAILED_MODE) {
                        std::cout << "Step " << i + 1 << std::endl;

                        std::cout
                            << (r_a == StrategyDecision::COOPERATE_DECISION
                                    ? "C"
                                    : "D")
                            << "\t:\t"
                            << (r_b == StrategyDecision::COOPERATE_DECISION
                                    ? "C"
                                    : "D")
                            << "\t:\t"
                            << (r_c == StrategyDecision::COOPERATE_DECISION
                                    ? "C"
                                    : "D")
                            << std::endl;

                        const auto [score_a, score_b, score_c] =
                            game.getScores();
                        std::cout << score_a << "\t:\t" << score_b << "\t:\t"
                                  << score_c << std::endl;
                        if (getchar() == 'q') {
                            arguments->mode = GameMode::TOURNAMENT_MODE;
                        }
                    }
                }

                if (arguments->mode == GameMode::DETAILED_MODE) {
                    game.printResults();
                    std::cout << std::endl;
                }

                strategies[a]->reset();
                strategies[b]->reset();
                strategies[c]->reset();

                const auto [score_a, score_b, score_c] = game.getScores();
                results[a] += score_a;
                results[b] += score_b;
                results[c] += score_c;
            }
        }
    }

    std::cout << "SUMMARY SCORE" << std::endl;
    for (size_t i = 0; i < strategies.size(); i++) {
        std::cout << strategies[i]->getName() << "\t:\t" << results[i]
                  << std::endl;
    }
}
