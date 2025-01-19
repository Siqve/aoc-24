```zsh
clang -g src/day1/day1a.c src/libs/aoc_lib.h src/libs/aoc_lib.c
leaks -atExit -- ./day1
```