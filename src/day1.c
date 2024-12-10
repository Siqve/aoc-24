#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getLineString(FILE *fptr) {
    char *lineString = malloc(15 * sizeof(char));
    if (!lineString) return NULL;
    if (fgets(lineString, 15, fptr) == NULL) {
        free(lineString);
        return NULL;
    }
    return lineString;
}

int main(void) {
    FILE *fptr = fopen("inputs/day1.txt", "r");

    int count = 0;
    int capacity = 10;
    int *A = malloc(capacity * sizeof(int));
    int *B = malloc(capacity * sizeof(int));
    char *lineString;
    while ((lineString = getLineString(fptr)) != NULL) {
        printf("a");
        if (count == capacity) {
            capacity *= 2;
            int *ATemp = realloc(A, capacity * sizeof(int));
            if (ATemp == NULL) {
                break;
            }
            int *BTemp = realloc(B, capacity * sizeof(int));
            if (BTemp == NULL) {
                break;
            }
            A = ATemp;
            B = BTemp;
        }
        const char *a = strtok(lineString, " ");
        const char *b = strtok(NULL, " ");
        A[count] = atoi(a);
        B[count] = atoi(b);
        count++;
        free(lineString);
        printf("%d\n", count);
    }
    free(lineString);

    printf("%d", A[999]);
    printf("%d", B[999]);

    free(A);
    free(B);
    fclose(fptr);
    return 0;
}
