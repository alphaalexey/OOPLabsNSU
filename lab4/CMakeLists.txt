# CMakeList.txt: проект CMake для lab4; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

project(lab4)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS
    "include/CSVParser.hpp")
set(SOURCES
    "src/main.cpp")
add_executable(lab4 ${SOURCES} ${HEADERS})
target_include_directories(lab4 PUBLIC "include")
