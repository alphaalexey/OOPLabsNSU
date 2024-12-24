#include <gtest/gtest.h>

#include "game.h"
#include "strategies/balance_strategy.h"
#include "strategies/cooperate_strategy.h"
#include "strategies/defect_strategy.h"
#include "strategies/kind_strategy.h"
#include "strategies/mirror_strategy.h"
#include "strategies/stat_strategy.h"
#include "strategy.h"

TEST(StrategyFactoryTest, TestCreateStrategy) {
    std::array<std::array<int, 3>, 8> matrix;
    std::shared_ptr<Strategy> strategy;

    strategy = StrategyFactory::createStrategy("balance", "", matrix);
    ASSERT_NE(strategy, nullptr);
    ASSERT_EQ(typeid(*strategy).name(), typeid(BalanceStrategy).name());

    strategy = StrategyFactory::createStrategy("cooperate", "", matrix);
    ASSERT_NE(strategy, nullptr);
    ASSERT_EQ(typeid(*strategy).name(), typeid(CooperateStrategy).name());

    strategy = StrategyFactory::createStrategy("defect", "", matrix);
    ASSERT_NE(strategy, nullptr);
    ASSERT_EQ(typeid(*strategy).name(), typeid(DefectStrategy).name());

    strategy = StrategyFactory::createStrategy("kind", "", matrix);
    ASSERT_NE(strategy, nullptr);
    ASSERT_EQ(typeid(*strategy).name(), typeid(KindStrategy).name());

    strategy = StrategyFactory::createStrategy("mirror", "", matrix);
    ASSERT_NE(strategy, nullptr);
    ASSERT_EQ(typeid(*strategy).name(), typeid(MirrorStrategy).name());

    strategy = StrategyFactory::createStrategy("stat", "", matrix);
    ASSERT_NE(strategy, nullptr);
    ASSERT_EQ(typeid(*strategy).name(), typeid(StatStrategy).name());

    ASSERT_THROW(StrategyFactory::createStrategy("unknown", "", matrix),
                 std::invalid_argument);
}

TEST(StrategyFactoryTest, TestGetAllStrategies) {
    std::vector<std::string> strategies = StrategyFactory::getAllStrategies();
    ASSERT_EQ(strategies.size(), 6);
    ASSERT_EQ(strategies[0], "balance");
    ASSERT_EQ(strategies[1], "cooperate");
    ASSERT_EQ(strategies[2], "defect");
    ASSERT_EQ(strategies[3], "kind");
    ASSERT_EQ(strategies[4], "mirror");
    ASSERT_EQ(strategies[5], "stat");
}

TEST(GameTest, TestPlayRound) {
    std::shared_ptr<Strategy> strategy_a =
        std::make_shared<CooperateStrategy>();
    std::shared_ptr<Strategy> strategy_b = std::make_shared<DefectStrategy>();
    std::shared_ptr<Strategy> strategy_c = std::make_shared<DefectStrategy>();
    std::array<std::array<int, 3>, 8> matrix = {
        std::array{1, 1, 1}, std::array{5, 5, 0}, std::array{5, 0, 5},
        std::array{9, 3, 3}, std::array{0, 5, 5}, std::array{3, 9, 3},
        std::array{3, 3, 9}, std::array{7, 7, 7}};

    auto game = Game(strategy_a, strategy_b, strategy_c, matrix);
    auto decisions = game.playRound();
    ASSERT_EQ(std::get<0>(decisions), StrategyDecision::COOPERATE_DECISION);
    ASSERT_EQ(std::get<1>(decisions), StrategyDecision::DEFECT_DECISION);
    ASSERT_EQ(std::get<2>(decisions), StrategyDecision::DEFECT_DECISION);

    ASSERT_EQ(game.getScores(), std::make_tuple(0, 5, 5));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
