#include "strategies/cooperate_strategy.h"

StrategyDecision CooperateStrategy::makeDecision() {
    return StrategyDecision::COOPERATE_DECISION;
}

void CooperateStrategy::addDecisions(
    const std::tuple<StrategyDecision, StrategyDecision> &opponent_decisions) {}

void CooperateStrategy::reset() {}
