cmake_minimum_required(VERSION 3.20)

project(lab0a)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS
    include/module1.h
    include/module2.h
    include/module3.h)
set(SOURCES
    src/module1.cpp
    src/module2.cpp
    src/module3.cpp
    src/main.cpp)

add_executable(lab0a ${SOURCES} ${HEADERS})
target_include_directories(lab0a PRIVATE include)
