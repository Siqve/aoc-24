#ifndef FILE_LIB_H
#define FILE_LIB_H

#include <stdio.h>
#include <stdbool.h>

typedef bool (*lineIterator)(char* line, void *arg);

typedef struct {
    int lineCount;
    int longestLineLength;
} FileInfo;

int getFirstFileLength(FILE *file);

FileInfo *getFileInfo(FILE *file, int maxLineLength);

char* getLineString(FILE* file, int maxLineLength);

bool iterateFileLines(FILE* file, int maxLineLength, lineIterator lineIterator, void *arg);

#endif //FILE_LIB_H
