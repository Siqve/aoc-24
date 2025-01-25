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

# Day 2 tasks
add_executable(day2a src/day2/day2a.c)
target_link_libraries(day2a aoc_libs)

add_executable(day2b src/day2/day2b.c)
target_link_libraries(day2b aoc_libs)

# Day 3 tasks
add_executable(day3a src/day3/day3a.c)
target_link_libraries(day3a aoc_libs)

add_executable(day3b src/day3/day3b.c)
target_link_libraries(day3b aoc_libs)

# Day 3 tasks
add_executable(day4a src/day4/day4a.c)
target_link_libraries(day4a aoc_libs)
