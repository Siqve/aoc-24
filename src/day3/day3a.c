#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libs/file_lib.h"


typedef struct {
    int x;
    int y;
} MultiplicationPair;


MultiplicationPair parseMul(char *mul) {

}

bool processLine(char *line, void *arg) {
    // TODO: Bruke strstr https://stackoverflow.com/questions/59770865/strtok-c-multiple-chars-as-one-delimiter
    strtok(line, "mul");
    char *nextMul = strtok(NULL, "mul(");
    return true;
}


int main() {
    FILE *file = fopen("inputs/day3.txt", "r");
    if (!file) {
        perror("Failed to open file: ");
        return EXIT_FAILURE;
    }

    if (!iterateFileLines(file, 100, processLine, NULL)) {
        fclose(file);
        return EXIT_FAILURE;
    }
}
