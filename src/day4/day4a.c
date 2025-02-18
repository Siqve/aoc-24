#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/file_lib.h"

enum { MAX_LINE_LENGTH = 200 };

typedef struct {
    char (*lines)[MAX_LINE_LENGTH];
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

static unsigned char DIRECTIONS_COUNT = 8;

char getCharInSequence(int index) {
    return "XMAS"[index];
}

void populateDirectionArray(Direction directions[8]) {
    directions[0] = TOP_LEFT;
    directions[1] = TOP;
    directions[2] = TOP_RIGHT;
    directions[3] = LEFT;
    directions[4] = RIGHT;
    directions[5] = BOTTOM_LEFT;
    directions[6] = BOTTOM;
    directions[7] = BOTTOM_RIGHT;
}

bool indexLine(char *line, void *arg) {
    LinesIndex *linesIndex = (LinesIndex *) arg;
    strcpy(linesIndex->lines[linesIndex->indexedLines], line);
    linesIndex->indexedLines += 1;
    return true;
}

int main() {
    FILE *file = fopen("inputs/day4.txt", "r");
    if (!file) {
        perror("Failed to open file: ");
        return EXIT_FAILURE;
    }

    FileInfo fileInfo = {};
    populateFileInfo(&fileInfo, file, 1000);
    if (fileInfo.longestLineLength > MAX_LINE_LENGTH) {
        fprintf(stderr, "Longest line length (%i) exceeds MAX_LINE_LENGTH (%i).", fileInfo.longestLineLength, MAX_LINE_LENGTH);
        return EXIT_FAILURE;
    }

    char lines[fileInfo.lineCount][MAX_LINE_LENGTH];
    LinesIndex linesIndex = {.lines = lines, .indexedLines = 0};

    int iteratorLineLength = fileInfo.longestLineLength + 2; // Plus two because of newline and null terminator
    if (!iterateFileLines(file, iteratorLineLength, indexLine, &linesIndex)) {
        return EXIT_FAILURE;
    }

    Direction directions[DIRECTIONS_COUNT];
    populateDirectionArray(directions);

    int counter = 0;
    for (int rowIndex = 0; rowIndex < linesIndex.indexedLines; rowIndex++) {
        for (int columnIndex = 0; columnIndex < fileInfo.longestLineLength; columnIndex++) {
            char c = lines[rowIndex][columnIndex];
            if (c != 'X')
                continue;
            for (int dirIndex = 0; dirIndex < DIRECTIONS_COUNT; dirIndex++) {
                Direction dir = directions[dirIndex];
                bool success = true;
                for (int i = 1; i < 4; i++) {
                    int cNextRow = rowIndex + (i * dir.rowChange);
                    int cNextColumn = columnIndex + (i * dir.columnChange);
                    if (cNextRow < 0 || cNextRow >= linesIndex.indexedLines) {
                        success = false;
                        break;
                    }
                    if (cNextColumn < 0 || cNextColumn >= fileInfo.longestLineLength) {
                        success = false;
                        break;
                    }
                    char cNext = lines[cNextRow][cNextColumn];
                    if (getCharInSequence(i) != cNext) {
                        success = false;
                        break;
                    }
                }
                if (success) {
                    counter++;
                }
            }

        }
    }

    printf("The sum is: %i", counter);
}
