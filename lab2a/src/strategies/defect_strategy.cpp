#include "strategies/defect_strategy.h"

StrategyDecision DefectStrategy::makeDecision() {
    return StrategyDecision::DEFECT_DECISION;
}

void DefectStrategy::addDecisions(
    const std::tuple<StrategyDecision, StrategyDecision> &opponent_decisions) {}

void DefectStrategy::reset() {}
