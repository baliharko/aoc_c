#include "str.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "input.txt"
#define LINE_MAX UINT16_MAX
#define GRID_SIZE 256

void resetGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    memset(grid, -1, sizeof(char) * GRID_SIZE * GRID_SIZE);
}

bool isMirrorVert(char grid[GRID_SIZE][GRID_SIZE], size_t index, size_t rows) {
    int64_t back = index - 1;
    int64_t front = index + 2;
    for (; back >= 0 && front < (int64_t)rows; back--, front++) {
        if (strncmp(grid[back], grid[front], GRID_SIZE) != 0) {
            return false; 
        }
    }
    
    return true;
}

bool isEqualColumns(char grid[GRID_SIZE][GRID_SIZE], size_t col1, size_t col2, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        if (grid[i][col1] != grid[i][col2]) 
            return false;
    }

    return true;
}

bool isMirrorHoriz(char grid[GRID_SIZE][GRID_SIZE], size_t index, size_t columns, size_t rows) {
    int64_t back = index - 1; 
    int64_t front = index + 2; 
    for (; back >= 0 && front < (int64_t)columns; back--, front++) {
        if (!isEqualColumns(grid, back, front, rows)) 
            return false;
    }

    return true;
}

uint64_t getPoints(char grid[GRID_SIZE][GRID_SIZE], size_t rows, size_t columns) {
    for (size_t i = 0; i < rows - 1; i++) {
        if (memcmp(grid[i], grid[i + 1], sizeof(char) * columns) == 0 
            && isMirrorVert(grid, i, rows)) {
            return 100 * (i + 1);
        }
    }

    for (size_t i = 0; i < columns - 1; i++) {
        if (isEqualColumns(grid, i, i + 1, rows) && isMirrorHoriz(grid, i, columns, rows)) {
            return i + 1; 
        }
    }

    return 0;
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
