#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../libs/file_lib.h"

static const unsigned char MAX_LINE_LENGTH = 100;

typedef struct {
    int *A;
    int *B;
    int arraySize;
    int capacity;
} ArrayData;

bool expandArray(int *capacity, int **A, int **B) {
    *capacity *= 2;
    int *ATemp = realloc(*A, *capacity * sizeof(int));
    int *BTemp = realloc(*B, *capacity * sizeof(int));
    if (ATemp) *A = ATemp;
    if (BTemp) *B = BTemp;
    return ATemp && BTemp;
}

void cleanUp(FILE *fptr, int *A, int *B) {
    if (fptr) fclose(fptr);
    free(A);
    free(B);
}

int compare(const void *a, const void *b) {
    const int *intA = (int *) a;
    const int *intB = (int *) b;
    return *intA - *intB;
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
    b[strcspn(b, "\n")] = 0; // Remove trailing newline
    arrayData->A[arrayData->arraySize] = atoi(a);
    arrayData->B[arrayData->arraySize] = atoi(b);
    arrayData->arraySize++;
    return true;
}

int main(void) {
    FILE *fptr = fopen("inputs/day1.txt", "r");
    if (!fptr) {
        perror("Failed to open file: ");
        return EXIT_FAILURE;
    }

    ArrayData arrayData;
    arrayData.arraySize = 0;
    arrayData.capacity = 10;
    arrayData.A = malloc(arrayData.capacity * sizeof(int));
    arrayData.B = malloc(arrayData.capacity * sizeof(int));
    if (!iterateFileLines(fptr, MAX_LINE_LENGTH, processLine, &arrayData)) {
        perror("Iterating file failed");
        cleanUp(fptr, arrayData.A, arrayData.B);
        return EXIT_FAILURE;
    }

    qsort(arrayData.A, arrayData.arraySize, sizeof(int), compare);
    qsort(arrayData.B, arrayData.arraySize, sizeof(int), compare);

    int diffSum = 0;
    for (int i = 0; i < arrayData.arraySize; i++) {
        diffSum += abs(arrayData.A[i] - arrayData.B[i]);
    }

    printf("Difference: %d", diffSum);
    cleanUp(fptr, arrayData.A, arrayData.B);
    return 0;
}
