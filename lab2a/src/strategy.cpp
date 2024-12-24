#include "strategy.h"

#include "strategies/balance_strategy.h"
#include "strategies/cooperate_strategy.h"
#include "strategies/defect_strategy.h"
#include "strategies/kind_strategy.h"
#include "strategies/mirror_strategy.h"
#include "strategies/stat_strategy.h"

std::shared_ptr<Strategy> StrategyFactory::createStrategy(
    const std::string &strategyName, const std::string &strategyConfig,
    const std::array<std::array<int, 3>, 8> &matrix) {
    if (strategyName == "balance") {
        return std::make_shared<BalanceStrategy>(matrix[4][0], matrix[7][0]);
    } else if (strategyName == "cooperate") {
        return std::make_shared<CooperateStrategy>();
    } else if (strategyName == "defect") {
        return std::make_shared<DefectStrategy>();
    } else if (strategyName == "kind") {
        return std::make_shared<KindStrategy>();
    } else if (strategyName == "mirror") {
        return std::make_shared<MirrorStrategy>();
    } else if (strategyName == "stat") {
        return std::make_shared<StatStrategy>();
    } else {
        throw std::invalid_argument("Unknown strategy: " + strategyName);
    }
}

const std::vector<std::string> StrategyFactory::getAllStrategies() {
    return {"balance", "cooperate", "defect", "kind", "mirror", "stat"};
}
