#include "strategies/stat_strategy.h"

StrategyDecision StatStrategy::makeDecision() {
    if (coop1 > defect1 && coop2 > defect2) {
        return StrategyDecision::COOPERATE_DECISION;
    } else {
        return StrategyDecision::DEFECT_DECISION;
    }
}

void StatStrategy::addDecisions(
    const std::tuple<StrategyDecision, StrategyDecision> &opponent_decisions) {
    const auto &[decision_a, decision_b] = opponent_decisions;
    if (decision_a == StrategyDecision::COOPERATE_DECISION) {
        coop1++;
    } else {
        defect1++;
    }
    if (decision_b == StrategyDecision::COOPERATE_DECISION) {
        coop2++;
    } else {
        defect2++;
    }
}

void StatStrategy::reset() { coop1 = coop2 = defect1 = defect2 = 0; }
