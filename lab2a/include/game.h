#pragma once

#include <array>
#include <memory>
#include <vector>

#include "strategy.h"

class Game {
private:
    std::array<std::shared_ptr<Strategy>, 3> strategies; // Стратегии игроков
    std::array<std::array<int, 3>, 8> payoffMatrix; // Матрица выплат
    std::array<int, 3> scores = {0, 0, 0};          // Очки игроков

public:
    Game(std::shared_ptr<Strategy> &strategy_a,
         std::shared_ptr<Strategy> &strategy_b,
         std::shared_ptr<Strategy> &strategy_c,
         const std::array<std::array<int, 3>, 8> &matrix);
    std::tuple<StrategyDecision, StrategyDecision, StrategyDecision>
    playRound();
    void printResults() const;
    std::tuple<int, int, int> getScores() const;
};
