#include "strategies/balance_strategy.h"

BalanceStrategy::BalanceStrategy(int win_cost, int loss_cost)
    : win_cost(win_cost), loss_cost(loss_cost) {}

StrategyDecision BalanceStrategy::makeDecision() {
    if (loss_cost * defs > win_cost * coops) {
        return StrategyDecision::DEFECT_DECISION;
    } else {
        return StrategyDecision::COOPERATE_DECISION;
    }
}

void BalanceStrategy::addDecisions(
    const std::tuple<StrategyDecision, StrategyDecision> &opponent_decisions) {
    const auto &[decision_a, decision_b] = opponent_decisions;
    if (decision_a == StrategyDecision::COOPERATE_DECISION) {
        coops++;
    } else {
        defs++;
    }
    if (decision_b == StrategyDecision::COOPERATE_DECISION) {
        coops++;
    } else {
        defs++;
    }
}

void BalanceStrategy::reset() { coops = defs = 0; }
