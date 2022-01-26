# CMakeList.txt : CMake project for CppUMockLifetimeIssue.
cmake_minimum_required(VERSION 3.20)

project("CppUMockLifetimeIssue")

set(CPPUTEST_PATH "C:/Dev/Tools/Cpputest-3.8/" CACHE PATH "Directory of CppUTest include files and libraries.")

# Set-up generic library with test runner, common dependencies, common compiler flags, and common include directories.
add_library(CommonLib EXCLUDE_FROM_ALL "TestRunner.cpp")


# Compile using Force Include files for the new and malloc wrappers. (Option in gcc is called -include.)
target_compile_options(CommonLib PUBLIC "/FI${CPPUTEST_PATH}\\include\\CppUTest\\MemoryLeakDetectorNewMacros.h"
                                        "/FI${CPPUTEST_PATH}\\include\\CppUTest\\MemoryLeakDetectorMallocMacros.h"
                                        "/fsanitize=address")

target_link_libraries(CommonLib PUBLIC "${CPPUTEST_PATH}/lib/CppUTestd.lib")

target_include_directories(CommonLib PUBLIC "${CPPUTEST_PATH}/include")

# Set-up tests for shared modules.
add_executable(TestRunner "SimpleTest.cpp" "CodeUnderTest.c")

target_link_libraries(TestRunner PRIVATE CommonLib)
