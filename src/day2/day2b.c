#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../libs/file_lib.h"

bool processLine(char *line, void *arg) {
    const char *firstNumberChar = strtok(line, " ");
    int firstNumber = atoi(firstNumberChar);
    bool initialized = false;
    bool increasing = false;

    bool hasPreviousUnsafeStep = false;
    bool progressNumberAnyway = false;

    char *currentNumberChar = strtok(NULL, " ");
    int previousNumber = firstNumber;
    while (currentNumberChar) {
        int currentNumber = atoi(currentNumberChar);
        if (!initialized) {
            increasing = previousNumber < currentNumber;
            initialized = true;
        }

        if (currentNumber == previousNumber) {
            if (hasPreviousUnsafeStep) {
                return true;
            }
            hasPreviousUnsafeStep = true;
        }

        if (increasing) {
            // Check if is increase
            if (currentNumber < previousNumber) {
                if (hasPreviousUnsafeStep) {
                    return true;
                }
                hasPreviousUnsafeStep = true;
            }
            // Make sure increase is at most 3
            if (currentNumber > previousNumber + 3) {
                if (hasPreviousUnsafeStep) {
                    return true;
                }
                hasPreviousUnsafeStep = true;
                progressNumberAnyway = true;

            }
        } else {
            // Check if is decrease
            if (currentNumber > previousNumber) {
                if (hasPreviousUnsafeStep) {
                    return true;
                }
                hasPreviousUnsafeStep = true;
            }
            // Make sure decrease is at most 3
            if (currentNumber < previousNumber - 3) {
                if (hasPreviousUnsafeStep) {
                    return true;
                }
                hasPreviousUnsafeStep = true;
                progressNumberAnyway = true;

            }
        }

        currentNumberChar = strtok(NULL, " ");
        if (!hasPreviousUnsafeStep || progressNumberAnyway) {
            // If has previousUnsafeStep is set to true, we skip this level
            previousNumber = currentNumber;
        }
    }
    *((int *) arg) += 1;
    return true;
}


int main() {
    FILE *fptr = fopen("inputs/day2.txt", "r");
    if (!fptr) {
        perror("Failed to open file: ");
        return EXIT_FAILURE;
    }

    int safeCount = 0;
    if (!iterateFileLines(fptr, 100, processLine, &safeCount)) {
        fclose(fptr);
    }

    printf("Safe numbers: %d\n", safeCount);

}