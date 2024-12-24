#pragma once

#include <string>

#include "strategy.h"

class StatStrategy : public Strategy {
private:
    int coop1 = 0, defect1 = 0;
    int coop2 = 0, defect2 = 0;

public:
    virtual ~StatStrategy() = default;

    const std::string getName() const override { return "StatStrategy"; };
    StrategyDecision makeDecision() override;
    void addDecisions(const std::tuple<StrategyDecision, StrategyDecision>
                          &opponent_decisions) override;
    void reset() override;
};
