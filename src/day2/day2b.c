#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../libs/file_lib.h"

bool isSafeLine(char *line, int indexToSkip) {
    char *firstNumberChar = strtok(line, " ");
    int currentIndex = 0;
    if (indexToSkip == currentIndex) {
        firstNumberChar = strtok(NULL, " ");
        if (!firstNumberChar) {
            return true;
        }
        currentIndex++;
    }

    int firstNumber = atoi(firstNumberChar);
    bool initialized = false;
    bool increasing = false;

    char *currentNumberChar = strtok(NULL, " ");
    currentIndex++;
    if (indexToSkip == currentIndex) {
        currentNumberChar = strtok(NULL, " ");
        if (!currentNumberChar) {
            return true;
        }
        currentIndex++;
    }
    int previousNumber = firstNumber;
    while (currentNumberChar) {
        int currentNumber = atoi(currentNumberChar);
        if (!initialized) {
            increasing = previousNumber < currentNumber;
            initialized = true;
        }
        if (increasing) {
            // Check if is increase
            if (currentNumber <= previousNumber) {
                return false;
            }
            // Make sure increase is at most 3
            if (currentNumber > previousNumber + 3) {
                return false;
            }
        } else {
            // Check if is decrease
            if (currentNumber >= previousNumber) {
                return false;
            }
            // Make sure decrease is at most 3
            if (currentNumber < previousNumber - 3) {
                return false;
            }
        }

        currentNumberChar = strtok(NULL, " ");
        currentIndex++;
        if (indexToSkip == currentIndex) {
            currentNumberChar = strtok(NULL, " ");
            currentIndex++;
        }
        previousNumber = currentNumber;
    }
    return true;
}

int countNumbers(const char *line) {
    size_t lineLength = strlen(line) + 1; // plus one for null terminator

    char *copy = malloc(lineLength * sizeof(char));
    if (!copy) {
        return -1;
    }
    strcpy(copy, line); // Use strdup in future

    int length = 0;
    char *splitPointer = strtok(copy, " ");
    while (splitPointer) {
        length++;
        splitPointer = strtok(NULL, " ");
    }

    free(copy);
    return length;
}

bool processLine(char *line, void *arg) {
    char *copy = strdup(line);
    if (isSafeLine(copy, -1)) {
        *((int *) arg) += 1;
        return true;
    }

    // Is unsafe at default line, starting to remove one and one index to see if it becomes safe
    int numbers = countNumbers(line);
    if (numbers == -1)
        return false;

    for (int i = 0; i < numbers; i++) {
        copy = strdup(line);
        if (isSafeLine(copy, i)) {
            *((int *) arg) += 1;
            return true;
        }
    }
    free(copy);
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

