#include "file_lib.h"

#include <stdlib.h>
#include <string.h>

char *getLineString(FILE *file, const int maxLineLength) {
    char *lineString = malloc(maxLineLength * sizeof(char));
    if (!lineString || !fgets(lineString, maxLineLength, file)) {
        free(lineString);
        return NULL;
    }
    lineString[strcspn(lineString, "\n")] = 0;
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

FileInfo *getFileInfo(FILE *file, int maxLineLength) {
    int lineCount = 0;
    int currentMaxLength = 0;
    char *lineString;

    while ((lineString = getLineString(file, maxLineLength))) {
        lineCount++;
        int length = (int) strlen(lineString);
        if (length > currentMaxLength)
            currentMaxLength = length;
        free(lineString);
    }

    free(lineString);
    FileInfo *fileInfo = malloc(sizeof (FileInfo*));
    fileInfo->lineCount = lineCount;
    fileInfo->longestLineLength = currentMaxLength;
    rewind(file);
    return fileInfo;
}

