#pragma once

#include <string>

#include "strategy.h"

class DefectStrategy : public Strategy {
public:
    virtual ~DefectStrategy() = default;

    const std::string getName() const override { return "DefectStrategy"; };
    StrategyDecision makeDecision() override;
    void addDecisions(const std::tuple<StrategyDecision, StrategyDecision>
                          &opponent_decisions) override;
    void reset() override;
};
