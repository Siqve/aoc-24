cmake_minimum_required(VERSION 3.29.6)
project(advent_of_code C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../")

set(CMAKE_C_STANDARD 17)

add_library(aoc_libs src/libs/file_lib.c src/libs/string_map.c)

# Day 1 tasks
add_executable(day1 src/day1/day1a.c)
target_link_libraries(day1 aoc_libs)

add_executable(day1b src/day1/day1b.c)
target_link_libraries(day1b aoc_libs)