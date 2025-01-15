#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libs/file_lib.h"

typedef struct {
    int x;
    int y;
} MultiplicationPair;

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

MultiplicationPair *parseMulPair(const char *s) {
    int startIndex = 4; // mul( = 4
    int charCheckerIndex = startIndex;
    if (s[charCheckerIndex] == '\0') {
        return NULL;
    }
    while (isDigit(s[charCheckerIndex])) {
        charCheckerIndex++;
    }

    // Check if any numbers on number one
    if (charCheckerIndex == startIndex) {
        return NULL;
    }
    if (s[charCheckerIndex] != ',') {
        return NULL;
    }
    int commaIndex = charCheckerIndex;
    charCheckerIndex++;
    while (isDigit(s[charCheckerIndex])) {
        charCheckerIndex++;
    }
    // Check if any numbers on number two
    if (charCheckerIndex == (commaIndex + 1)) {
        return NULL;
    }
    if (s[charCheckerIndex] != ')') {
        return NULL;
    }

    int numberOneCharLength = commaIndex - startIndex;
    int numberTwoCharLength = charCheckerIndex - (commaIndex + 1);

    char *numberOneString = malloc(numberOneCharLength + 1);
    if (!numberOneString) {
        return NULL;
    }
    char *numberTwoString = malloc(numberTwoCharLength + 1);
    if (!numberTwoCharLength) {
        free(numberOneString);
        return NULL;
    }
    strncpy(numberOneString, s + startIndex, numberOneCharLength);
    numberOneString[numberOneCharLength] = '\0';
    strncpy(numberTwoString, s + commaIndex + 1, numberTwoCharLength);
    numberTwoString[numberTwoCharLength] = '\0';

    MultiplicationPair *pair = malloc(sizeof(*pair));
    if (!pair) {
        free(numberOneString);
        free(numberTwoString);
        return NULL;
    }

    pair->x = strtol(numberOneString, NULL, 10);
    pair->y = strtol(numberTwoString, NULL, 10);

    free(numberOneString);
    free(numberTwoString);
    return pair;
}

bool processLine(char *line, void *arg) {
    char *nextMul = line;
    while ((nextMul = strstr(nextMul, "mul("))) {
        MultiplicationPair *pair = parseMulPair(nextMul);
        nextMul+=1;
        if (!pair) {
            continue;
        }
        long *sum = (long *) arg;
        *sum += pair->x * pair->y;
        free(pair);
    }

    return true;
}


int main() {
    FILE *file = fopen("inputs/day3.txt", "r");
    if (!file) {
        perror("Failed to open file: ");
        return EXIT_FAILURE;
    }

    long sum = 0;
    if (!iterateFileLines(file, 4000, processLine, &sum)) {
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("The sum is: %ld", sum);
}
