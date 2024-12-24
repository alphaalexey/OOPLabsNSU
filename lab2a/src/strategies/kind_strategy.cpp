#include "strategies/kind_strategy.h"

StrategyDecision KindStrategy::makeDecision() {
    return kind ? StrategyDecision::COOPERATE_DECISION
                : StrategyDecision::DEFECT_DECISION;
}

void KindStrategy::addDecisions(
    const std::tuple<StrategyDecision, StrategyDecision> &opponent_decisions) {
    const auto &[decision_a, decision_b] = opponent_decisions;
    if (decision_a != StrategyDecision::COOPERATE_DECISION ||
        decision_b != StrategyDecision::COOPERATE_DECISION) {
        kind = false; // time for blood
    }
}

void KindStrategy::reset() { kind = true; }
