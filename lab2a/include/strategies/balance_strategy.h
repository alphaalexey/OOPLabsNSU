#pragma once

#include <string>

#include "strategy.h"

class BalanceStrategy : public Strategy {
private:
    int win_cost, loss_cost;
    int coops = 0, defs = 0;

public:
    BalanceStrategy(int win_cost, int loss_cost);
    virtual ~BalanceStrategy() = default;

    const std::string getName() const override { return "BalanceStrategy"; };
    StrategyDecision makeDecision() override;
    void addDecisions(const std::tuple<StrategyDecision, StrategyDecision>
                          &opponent_decisions) override;
    void reset() override;
};
