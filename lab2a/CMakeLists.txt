# CMakeList.txt: проект CMake для lab2a; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

project(lab2a)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS
    "include/strategies/balance_strategy.h"
    "include/strategies/cooperate_strategy.h"
    "include/strategies/defect_strategy.h"
    "include/strategies/kind_strategy.h"
    "include/strategies/mirror_strategy.h"
    "include/strategies/stat_strategy.h"
    "include/game.h"
    "include/strategy.h")
set(SOURCES
    "src/strategies/balance_strategy.cpp"
    "src/strategies/cooperate_strategy.cpp"
    "src/strategies/defect_strategy.cpp"
    "src/strategies/kind_strategy.cpp"
    "src/strategies/mirror_strategy.cpp"
    "src/strategies/stat_strategy.cpp"
    "src/game.cpp"
    "src/strategy.cpp"
    "src/main.cpp")
add_executable(lab2a ${SOURCES} ${HEADERS})
target_include_directories(lab2a PUBLIC "include")

# Тестирование
set(TEST_SOURCES
    "src/strategies/balance_strategy.cpp"
    "src/strategies/cooperate_strategy.cpp"
    "src/strategies/defect_strategy.cpp"
    "src/strategies/kind_strategy.cpp"
    "src/strategies/mirror_strategy.cpp"
    "src/strategies/stat_strategy.cpp"
    "src/game.cpp"
    "src/strategy.cpp"
    "test/game_test.cpp")
add_executable(lab2a_test ${TEST_SOURCES} ${HEADERS})
target_link_libraries(lab2a_test PRIVATE GTest::gtest)
target_include_directories(lab2a_test PUBLIC "include")

include(GoogleTest)
gtest_discover_tests(lab2a_test)
