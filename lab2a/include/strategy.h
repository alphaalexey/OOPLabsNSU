#pragma once

#include <array>
#include <memory>
#include <vector>

enum class StrategyDecision {
    COOPERATE_DECISION,
    DEFECT_DECISION,
};

class Strategy {
public:
    virtual ~Strategy() = default;

    inline virtual const std::string getName() const = 0;
    virtual StrategyDecision makeDecision() = 0; // Возвращает 'C' или 'D'
    virtual void
    addDecisions(const std::tuple<StrategyDecision, StrategyDecision>
                     &opponent_decisions) = 0; // Обновляет историю ходов
    virtual void reset() = 0;
};

class StrategyFactory {
private:
    StrategyFactory() = delete;

public:
    static std::shared_ptr<Strategy>
    createStrategy(const std::string &strategyName,
                   const std::string &strategyConfig,
                   const std::array<std::array<int, 3>, 8> &matrix);
    static const std::vector<std::string> getAllStrategies();
};
