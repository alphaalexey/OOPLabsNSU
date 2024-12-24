# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную
# конфигурацию и включите сюда подпроекты.
#
cmake_minimum_required(VERSION 3.14)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()
# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
        "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>"
    )
endif()

project("OOP_LABS")

#
# TESTING
#
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/e54519b09463cec3aea77a1739e02c97ca766da5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Включите подпроекты.
add_subdirectory("lab0a")
add_subdirectory("lab0b")
add_subdirectory("lab1a")
add_subdirectory("lab2a")
add_subdirectory("lab3")
