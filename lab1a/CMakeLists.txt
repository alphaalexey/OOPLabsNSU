# CMakeList.txt: проект CMake для lab1a; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

project(lab1a)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS "include/bit_array.h")
set(SOURCES "src/bit_array.cpp")
add_library(lab1a STATIC ${SOURCES} ${HEADERS})
target_include_directories(lab1a PUBLIC "include")

# Тестирование
set(TEST_SOURCES "test/bit_array_test.cpp")
add_executable(lab1a_test ${TEST_SOURCES})
target_link_libraries(lab1a_test PRIVATE GTest::gtest_main lab1a)

# BITARRAY2
set(HEADERS "include/bit_array2.h")
set(SOURCES "src/bit_array2.cpp")
add_library(lab1a_2 STATIC ${SOURCES} ${HEADERS})
target_include_directories(lab1a_2 PUBLIC "include")

# Тестирование
set(TEST_SOURCES "test/bit_array_test2.cpp")
add_executable(lab1a_2_test ${TEST_SOURCES})
target_link_libraries(lab1a_2_test PRIVATE GTest::gtest_main lab1a_2)

include(GoogleTest)
gtest_discover_tests(lab1a_test)
gtest_discover_tests(lab1a_2_test)
