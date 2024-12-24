# CMakeList.txt: проект CMake для lab3; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

project(lab3)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS
    "include/cfg_parser.h"
    "include/converter.h"
    "include/processor.h"
    "include/wav_file.h")
set(SOURCES
    "src/cfg_parser.cpp"
    "src/converter.cpp"
    "src/processor.cpp"
    "src/wav_file.cpp"
    "src/main.cpp")
add_executable(lab3 ${SOURCES} ${HEADERS})
target_include_directories(lab3 PUBLIC "include")
