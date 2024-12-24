#include "strategies/mirror_strategy.h"

StrategyDecision MirrorStrategy::makeDecision() { return last_decision; }

void MirrorStrategy::addDecisions(
    const std::tuple<StrategyDecision, StrategyDecision> &opponent_decisions) {
    std::tie(last_decision, std::ignore) = opponent_decisions;
}

void MirrorStrategy::reset() {
    last_decision = StrategyDecision::COOPERATE_DECISION;
}
