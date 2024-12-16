#ifndef FILE_LIB_H
#define FILE_LIB_H

#include <stdio.h>
#include <stdbool.h>

typedef bool (*lineIterator)(char* line, void *arg);

char* getLineString(FILE* file, int maxLineLength);

bool iterateFileLines(FILE* file, int maxLineLength, lineIterator lineIterator, void *arg);

#endif //FILE_LIB_H
