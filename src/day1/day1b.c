#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../libs/string_map.h"
#include "../libs/file_lib.h"

static const unsigned char MAX_LINE_LENGTH = 100;
static const unsigned char MAX_KEY_SIZE = 10;

typedef struct {
    char **A;
    char **B;
    int arraySize;
    int capacity;
} ArrayData;

bool expandArray(int *capacity, char ***A, char ***B) {
    *capacity *= 2;
    char **ATemp = realloc(*A, *capacity * sizeof(char *));
    char **BTemp = realloc(*B, *capacity * sizeof(char *));
    if (ATemp) *A = ATemp;
    if (BTemp) *B = BTemp;
    return ATemp && BTemp;
}

void cleanUp(FILE *fptr, const ArrayData *arrayData) {
    if (fptr) fclose(fptr);
    for (int i = 0; i < arrayData->arraySize; i++) {
        free(arrayData->A[i]);
    }
    free(arrayData->A);
    for (int i = 0; i < arrayData->arraySize; i++) {
        free(arrayData->B[i]);
    }
    free(arrayData->B);
}

bool indexOccurrences(char **B, StringMap *map, int occurrences[], const int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        char *b = B[i];
        const int index = StringMap_getIndex(map, b);
        if (index == -1) {
            // First appearance
            const int newIndex = StringMap_insert(map, b);
            if (newIndex == -1) {
                return false;
            }
            occurrences[newIndex] = 1;
        } else {
            // Occurring once more
            occurrences[index] += 1;
        }
    }
    return true;
}

bool processLine(char *line, void *arg) {
    ArrayData *arrayData = (ArrayData *) arg;
    if (arrayData->arraySize == arrayData->capacity) {
        if (!expandArray(&arrayData->capacity, &arrayData->A, &arrayData->B)) {
            return false;
        }
    }
    const char *a = strtok(line, " ");
    char *b = strtok(NULL, " ");
    if (!a || !b) {
        return false;
    }

    char *aInArray = arrayData->A[arrayData->arraySize] = malloc(MAX_KEY_SIZE * sizeof(char));
    if (!aInArray) {
        return false;
    }
    strcpy(aInArray, a);

    char *bInArray = arrayData->B[arrayData->arraySize] = malloc(MAX_KEY_SIZE * sizeof(char));
    if (!bInArray) {
        return false;
    }
    strcpy(bInArray, b);
    arrayData->arraySize++;
    return true;
}

int main(void) {
    FILE *fptr = fopen("inputs/day1.txt", "r");
    if (!fptr) {
        perror("Failed to open file: ");
        return EXIT_FAILURE;
    }

    // int arraySize = 0;
    // int capacity = 10;
    // char **A = malloc(capacity * sizeof(char *));
    // char **B = malloc(capacity * sizeof(char *));
    ArrayData arrayData;
    arrayData.arraySize = 0;
    arrayData.capacity = 10;
    arrayData.A = malloc(arrayData.capacity * sizeof(char *));
    arrayData.B = malloc(arrayData.capacity * sizeof(char *));

    if (!iterateFileLines(fptr, 100, processLine, &arrayData)) {
        cleanUp(fptr, &arrayData);
        return EXIT_FAILURE;
    }

    //TODO: Make it work with this new iterateFileLines setup, currently outputs sum: 0
    // but it worked with the commented out approach hmmmm
    //
    //
    // char *lineString;
    // while ((lineString = getLineString(fptr, MAX_LINE_LENGTH))) {
    //     if (arraySize == capacity) {
    //         if (!expandArray(&capacity, &A, &B)) {
    //             cleanUp(fptr, A, B, arraySize);
    //             free(lineString);
    //             return EXIT_FAILURE;
    //         }
    //     }
    //     const char *a = strtok(lineString, " ");
    //     char *b = strtok(NULL, " ");
    //     if (!a || !b) {
    //         cleanUp(fptr, A, B, arraySize);
    //         free(lineString);
    //         return EXIT_FAILURE;
    //     }
    //     b[strcspn(b, "\n")] = 0; // Remove trailing newline
    //
    //     char *aInArray = A[arraySize] = malloc(MAX_KEY_SIZE * sizeof(char));
    //     if (!aInArray) {
    //         perror("Failed to allocate memory for A[arraySize]");
    //         cleanUp(fptr, A, B, arraySize);
    //         free(lineString);
    //         return EXIT_FAILURE;
    //     }
    //     strcpy(aInArray, a);
    //
    //     char *bInArray = B[arraySize] = malloc(MAX_KEY_SIZE * sizeof(char));
    //     if (!bInArray) {
    //         perror("Failed to allocate memory for B[arraySize]");
    //         cleanUp(fptr, A, B, arraySize);
    //         free(lineString);
    //         return EXIT_FAILURE;
    //     }
    //     strcpy(bInArray, b);
    //     arraySize++;
    //     free(lineString);
    // }

    int occurrences[arrayData.arraySize];
    StringMap *map = StringMap_create(10, MAX_KEY_SIZE);
    if (!indexOccurrences(arrayData.B, map, occurrences, arrayData.arraySize)) {
        StringMap_destroy(map);
        cleanUp(fptr, &arrayData);
        return EXIT_FAILURE;
    }

    int sum = 0;
    for (int i = 0; i < arrayData.arraySize; i++) {
        char *a = arrayData.A[i];
        const int index = StringMap_getIndex(map, a);
        if (index == -1) {
            // If no occurrences, then sum is unchanged
            continue;
        }
        printf("index: %d\n", index);
        const int impact = atoi(a) * occurrences[index];
        sum += impact;
    }

    printf("Sum: %d", sum);
    StringMap_destroy(map);
    cleanUp(fptr, &arrayData);
    return 0;
}
