#include "file_lib.h"

#include <stdlib.h>


char *getLineString(FILE *file, const int maxLineLength) {
    char *lineString = malloc(maxLineLength * sizeof(char));
    if (!lineString || !fgets(lineString, maxLineLength, file)) {
        free(lineString);
        return NULL;
    }
    return lineString;
}

bool iterateFileLines(FILE *file, const int maxLineLength, const lineIterator lineIterator, void *arg) {
    char *lineString;
    while ((lineString = getLineString(file, maxLineLength))) {
        if (!lineIterator(lineString, arg)) {
            free(lineString);
            return false;
        }
        free(lineString);
    }
    free(lineString);
    return true;
}
