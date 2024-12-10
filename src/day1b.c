#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const unsigned char MAX_LINE_LENGTH = 100;
static const unsigned char MAX_KEY_SIZE = 10;

bool expandArray(int* capacity, char*** A, char*** B) {
    (*capacity) *= 2;
    char** ATemp = realloc((*A), (*capacity) * sizeof(char*));
    char** BTemp = realloc((*B), (*capacity) * sizeof(char*));
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

void cleanUp(FILE* fptr, char** A, char** B, int arraySize) {
    if (fptr) fclose(fptr);
    for (int i = 0; i < arraySize; i++) {
        free(A[i]);
    }
    free(A);
    for (int i = 0; i < arraySize; i++) {
        free(B[i]);
    }
    free(B);
}

int getIndex(int keysSize, char keys[keysSize][MAX_KEY_SIZE], char key[]) {
    for (int i = 0; i < keysSize; i++) {
        if (strcmp(keys[i], key) == 0) {
            return i;
        }
    }
    return -1;
}

void insert(int* keysSize, char keys[*keysSize + 1][MAX_KEY_SIZE], int occurrences[*keysSize], const char key[MAX_KEY_SIZE]) {
    strcpy(keys[*keysSize], key);
    occurrences[*keysSize] = 1;
    (*keysSize)++;
}

void indexOccurrences(int arraySize, int* keysSize, char keys[*keysSize + 1][MAX_KEY_SIZE], int occurrences[*keysSize], char** B) {
    for (int i = 0; i < arraySize; i++) {
        char* b = B[i];
        int index = getIndex(*keysSize, keys, b);
        if (index == -1) {
            // First appearance
            insert(keysSize, keys, occurrences, b);
        } else {
            // Occurring once more
            occurrences[index] += 1;
        }
    }
}

int main(void) {
    FILE* fptr = fopen("inputs/day1.txt", "r");
    if (!fptr) {
        perror("Failed to open file: ");
        return EXIT_FAILURE;
    }

    int arraySize = 0;
    int capacity = 10;
    char** A = malloc(capacity * sizeof(char*));
    char** B = malloc(capacity * sizeof(char*));

    char* lineString;
    while ((lineString = getLineString(fptr))) {
        if (arraySize == capacity) {
            if (!expandArray(&capacity, &A, &B)) {
                cleanUp(fptr, A, B, arraySize);
                free(lineString);
                return EXIT_FAILURE;
            }
        }
        const char* a = strtok(lineString, " ");
        char* b = strtok(NULL, " ");
        if (!a || !b) {
            cleanUp(fptr, A, B, arraySize);
            free(lineString);
            return EXIT_FAILURE;
        }
        b[strcspn(b, "\n")] = 0; // Remove trailing newline

        char* aInArray = A[arraySize] = malloc(MAX_KEY_SIZE * sizeof(char));
        if (!aInArray) {
            perror("Failed to allocate memory for A[arraySize]");
            cleanUp(fptr, A, B, arraySize);
            free(lineString);
            return EXIT_FAILURE;
        }
        strcpy(aInArray, a);

        char* bInArray = B[arraySize] = malloc(MAX_KEY_SIZE * sizeof(char));
        if (!bInArray) {
            perror("Failed to allocate memory for B[arraySize]");
            cleanUp(fptr, A, B, arraySize);
            free(lineString);
            return EXIT_FAILURE;
        }
        strcpy(bInArray, b);
        arraySize++;
        free(lineString);
    }

    char keys[arraySize][MAX_KEY_SIZE]; // Array to store the keys
    int keysSize = 0;
    int occurrences[arraySize];

    indexOccurrences(arraySize, &keysSize, keys, occurrences, B);

    int sum = 0;
    for (int i = 0; i < arraySize; i++) {
        char* a = A[i];
        int index = getIndex(keysSize, keys, a);
        if (index == -1) {
            // If no occurrences, then sum is unchanged
            continue;
        }
        int impact = atoi(a) * occurrences[index];
        sum += impact;
    }

    printf("Sum: %d", sum);
    cleanUp(fptr, A, B, arraySize);
    return 0;
}


