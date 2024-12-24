#include "game.h"

#include <iostream>

Game::Game(std::shared_ptr<Strategy> &strategy_a,
           std::shared_ptr<Strategy> &strategy_b,
           std::shared_ptr<Strategy> &strategy_c,
           const std::array<std::array<int, 3>, 8> &matrix)
    : strategies(std::array{strategy_a, strategy_b, strategy_c}),
      payoffMatrix(matrix) {}

std::tuple<StrategyDecision, StrategyDecision, StrategyDecision>
Game::playRound() {
    StrategyDecision a_decision = strategies[0]->makeDecision();
    StrategyDecision b_decision = strategies[1]->makeDecision();
    StrategyDecision c_decision = strategies[2]->makeDecision();

    int y = (a_decision == StrategyDecision::COOPERATE_DECISION) ? 1 : 0;
    y <<= 1;
    y += (b_decision == StrategyDecision::COOPERATE_DECISION) ? 1 : 0;
    y <<= 1;
    y += (c_decision == StrategyDecision::COOPERATE_DECISION) ? 1 : 0;

    const auto &payoff = payoffMatrix[y];
    scores[0] += payoff[0];
    scores[1] += payoff[1];
    scores[2] += payoff[2];

    strategies[0]->addDecisions({b_decision, c_decision});
    strategies[1]->addDecisions({a_decision, c_decision});
    strategies[2]->addDecisions({a_decision, b_decision});

    return {a_decision, b_decision, c_decision};
}

void Game::printResults() const {
    std::cout << "------------------" << std::endl;
    std::cout << "Scores: " << scores[0] << " : " << scores[1] << " : "
              << scores[2] << std::endl;

    for (int i = 0; i < strategies.size(); i++) {
        std::cout << "Strategy " << strategies[i]->getName()
                  << " score: " << scores[i] << std::endl;
    }
}

std::tuple<int, int, int> Game::getScores() const {
    return {scores[0], scores[1], scores[2]};
}
