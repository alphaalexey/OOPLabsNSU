#pragma once

#include <string>

#include "strategy.h"

class KindStrategy : public Strategy {
private:
    bool kind = true;

public:
    virtual ~KindStrategy() = default;

    const std::string getName() const override { return "KindStrategy"; };
    StrategyDecision makeDecision() override;
    void addDecisions(const std::tuple<StrategyDecision, StrategyDecision>
                          &opponent_decisions) override;
    void reset() override;
};
