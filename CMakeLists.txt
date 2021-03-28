cmake_minimum_required(VERSION 3.17)
project(nahfstocks)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall -Werror -pedantic)

add_definitions(-D"${TEST_VAR}")

add_executable(nahfstocks src/main.cpp tests/Tests.cpp tests/Tests.h lib/gtest_lite.h lib/memtrace.h lib/memtrace.cpp)