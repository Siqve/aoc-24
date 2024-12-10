#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const unsigned char MAX_LINE_LENGTH = 100;

bool expandArray(int* capacity, int** A, int** B) {
    (*capacity) *= 2;
    int* ATemp = realloc((*A), (*capacity) * sizeof(int));
    int* BTemp = realloc((*B), (*capacity) * sizeof(int));
    if (ATemp) (*A) = ATemp;
    if (BTemp) (*B) = BTemp;
    return ATemp && BTemp;
}

char* getLineString(FILE* fptr) {
    char* lineString = malloc(MAX_LINE_LENGTH * sizeof(char));
    if (!lineString || !fgets(lineString, MAX_LINE_LENGTH, fptr)) {
        free(lineString);
        return NULL;
    }
    return lineString;
}

void cleanUp(FILE* fptr, int* A, int* B) {
    if (fptr) fclose(fptr);
    free(A);
    free(B);
}

int compare(const void* a, const void* b) {
    const int* intA = (int*) a;
    const int* intB = (int*) b;
    return *intA - *intB;
}

int main(void) {
    FILE* fptr = fopen("inputs/day1.txt", "r");
    if (!fptr) {
        perror("Failed to open file: ");
        return EXIT_FAILURE;
    }

    int arraySize = 0;
    int capacity = 10;
    int* A = malloc(capacity * sizeof(int));
    int* B = malloc(capacity * sizeof(int));
    char* lineString;
    while ((lineString = getLineString(fptr))) {
        if (arraySize == capacity) {
            if (!expandArray(&capacity, &A, &B)) {
                cleanUp(fptr, A, B);
                free(lineString);
                return EXIT_FAILURE;
            }
        }
        const char* a = strtok(lineString, " ");
        const char* b = strtok(NULL, " ");
        if (!a || !b) {
            cleanUp(fptr, A, B);
            free(lineString);
            return EXIT_FAILURE;
        }
        A[arraySize] = atoi(a);
        B[arraySize] = atoi(b);
        arraySize++;
        free(lineString);
    }

    qsort(A, arraySize, sizeof(int), compare);
    qsort(B, arraySize, sizeof(int), compare);

    int diffSum = 0;
    for (int i = 0; i < arraySize; i++) {
        diffSum +=abs(A[i] - B[i]);
    }

    printf("Difference: %d", diffSum);

    cleanUp(fptr, A, B);
    return 0;
}
