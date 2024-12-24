#pragma once

#include <string>

#include "strategy.h"

class MirrorStrategy : public Strategy {
protected:
    StrategyDecision last_decision = StrategyDecision::COOPERATE_DECISION;

public:
    virtual ~MirrorStrategy() = default;

    const std::string getName() const override { return "MirrorStrategy"; };
    StrategyDecision makeDecision() override;
    void addDecisions(const std::tuple<StrategyDecision, StrategyDecision>
                          &opponent_decisions) override;
    void reset() override;
};
