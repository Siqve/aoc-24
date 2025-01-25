#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/file_lib.h"

typedef struct {
    char **lines;
    int indexedLines;
} LinesIndex;

typedef struct {
    int rowChange;
    int columnChange;
} Direction;

Direction TOP_LEFT = {.rowChange = -1, .columnChange = -1};
Direction TOP = {.rowChange = -1, .columnChange = 0};
Direction TOP_RIGHT = {.rowChange = -1, .columnChange = 1};
Direction LEFT = {.rowChange = 0, .columnChange = -1};
Direction RIGHT = {.rowChange = 0, .columnChange = 1};
Direction BOTTOM_LEFT = {.rowChange = 1, .columnChange = -1};
Direction BOTTOM = {.rowChange = 1, .columnChange = 0};
Direction BOTTOM_RIGHT = {.rowChange = 1, .columnChange = 1};

bool indexLine(char *line, void *arg) {
    LinesIndex *linesIndex = (LinesIndex *) arg;
    int lineLength = (int) strlen(line);
    char *lineCopy = calloc(lineLength + 1, sizeof (char));
    strncpy(lineCopy, line, lineLength);
    linesIndex->lines[linesIndex->indexedLines] = lineCopy;
    linesIndex->indexedLines += 1;
    return true;
}

bool clearLinesIndex(LinesIndex *linesIndex) {
    for (int i = 0; i < linesIndex->indexedLines; i++) {
        free(linesIndex->lines[i]);
    }
    free(linesIndex->lines);
    return true;
}

int main() {
    FILE *file = fopen("inputs/day4.txt", "r");
    if (!file) {
        perror("Failed to open file: ");
        return EXIT_FAILURE;
    }

    FileInfo *fileInfo = getFileInfo(file, 1000);
    char **lines = malloc(fileInfo->lineCount * sizeof(char *));
    LinesIndex linesIndex = {.lines = lines, .indexedLines = 0};

    int iteratorLineLength = fileInfo->longestLineLength + 2; // Plus two because of newline and null terminator
    if (!iterateFileLines(file, iteratorLineLength, indexLine, &linesIndex)) {
        clearLinesIndex(&linesIndex);
        free(lines);
        free(fileInfo);
        return EXIT_FAILURE;
    }

    for (int rowIndex = 0; rowIndex < linesIndex.indexedLines; rowIndex++) {
        for (int columnIndex = 0; columnIndex < fileInfo->longestLineLength; columnIndex++) {
            //TODO: For hver character, sjekk alle retninger om match
            //  hvis match, sjekk så neste i samme retning for match
            //  dette vil, tror jeg, finne 4 ganger riktig antall, så total match / 4 vil være riktig svar hmm
        }
    }


    clearLinesIndex(&linesIndex);
    free(fileInfo);

//    printf("The sum is: %ld", lineLength);
}
