#pragma once

#include <string>

#include "strategy.h"

class CooperateStrategy : public Strategy {
public:
    virtual ~CooperateStrategy() = default;

    const std::string getName() const override { return "CoopStrategy"; };
    StrategyDecision makeDecision() override;
    void addDecisions(const std::tuple<StrategyDecision, StrategyDecision>
                          &opponent_decisions) override;
    void reset() override;
};
