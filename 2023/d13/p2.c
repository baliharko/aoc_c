#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

#define FILE_NAME "input.txt"
#define LINE_MAX UINT16_MAX
#define GRID_SIZE 256

void resetGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    memset(grid, -1, sizeof(char) * GRID_SIZE * GRID_SIZE);
}

unsigned int strDiff(const char *a, const char *b, size_t len) {
    unsigned int diff = 0;
    for (size_t i = 0; i < len; i++) {
        if (a[i] != b[i]) diff++;
    }

    return diff;
}

bool isHorizontalMirror(char grid[GRID_SIZE][GRID_SIZE], size_t index, size_t rows, size_t columns, unsigned int acc) {
    unsigned int diff = acc;
    int64_t back = index - 1;
    int64_t front = index + 2;
    for (; back >= 0 && front < (int64_t)rows; back--, front++) {
        for (size_t i = 0; i < columns; i++) {
            if (grid[back][i] != grid[front][i]) 
                diff++;
        }
    }
    return diff == 1;
}


unsigned int getColumnsDiff(char grid[GRID_SIZE][GRID_SIZE], size_t col1, size_t col2, size_t rows) {
    unsigned int diff = 0;
    for (size_t i = 0; i < rows; i++) {
        if (grid[i][col1] != grid[i][col2]) 
            diff++;
    }

    return diff;
}

bool isVerticalMirror(char grid[GRID_SIZE][GRID_SIZE], size_t index, size_t columns, size_t rows, unsigned int acc) {
    unsigned int diff = acc;
    int64_t back = index - 1; 
    int64_t front = index + 2; 
    for (; back >= 0 && front < (int64_t)columns; back--, front++) {
        diff += getColumnsDiff(grid, back, front, rows);
    }

    return diff == 1;
}

uint64_t getPoints(char grid[GRID_SIZE][GRID_SIZE], size_t rows, size_t columns) {
    uint64_t points = 0;
    for (size_t i = 0; i < columns - 1; i++) {
        unsigned int diff = getColumnsDiff(grid, i, i + 1, rows);
        if (diff <= 1 && isVerticalMirror(grid, i, columns, rows, diff)) {
            points = i + 1; 
        }
    }

    if (points > 0) 
        return points;

    for (size_t i = 0; i < rows - 1; i++) {
        unsigned int diff = strDiff(grid[i], grid[i + 1], columns);
        if (diff <= 1 && isHorizontalMirror(grid, i, rows, columns, diff))
            points = 100 * (i + 1);
    }

    return points;
}

int main(void) {
    FILE *input = fopen("2023/d13/" FILE_NAME, "r");
    if (!input) {
        perror("Error opening file, exiting.\n");
    }

    int columnCount = 0;
    int rowsCount = 0;
    char gridBuffer[256][256] = { {-1} };
    char line[LINE_MAX];

    uint64_t ans = 0;
    do {
        if (fgets(line, LINE_MAX, input) == NULL || line[0] == '\n') {
            if (rowsCount > 0) {
                uint64_t points = getPoints(gridBuffer, rowsCount, columnCount);
                ans += points;
                resetGrid(gridBuffer);
            }

            columnCount = 0;
            rowsCount = 0;
            if (feof(input)) 
                break;

            continue;
        }

        if (rowsCount == 0) {
            columnCount = indexof_c(line, '\n');
        }

        for (int i = 0; i < columnCount; i++) {
            gridBuffer[rowsCount][i] = line[i];
        }

        gridBuffer[rowsCount][columnCount + 1] = '\0';
        rowsCount++;
    } while (!feof(input));
    fclose(input);

    printf("ans: %llu\n", ans);
    return 0;
}
