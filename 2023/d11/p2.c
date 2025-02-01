#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#define FILE_NAME "input.txt"

int main(void) {
    FILE *input = fopen("2023/d11/" FILE_NAME, "r");
    if (input == NULL) {
        perror("Error opening file. Exiting.");
        return -1;
    }

    int initialWidth = 0, initialHeight = 0;
    getInputDimensions(input, &initialWidth, &initialHeight);

    bool emptyLine[initialHeight], emptyCol[initialWidth];
    for (int i = 0; i < initialHeight; i++) emptyLine[i] = true;
    for (int i = 0; i < initialWidth; i++) emptyCol[i] = true;

    Point grid[initialWidth * initialHeight + 1];
    for (int i = 0; i < initialWidth * initialHeight; i++) {
        Point p;
        p.x = 0;
        p.y = 0;
        p.isGalaxy = false;
        grid[i] = p;
    }

    int galaxiesCount = 0;
    char line[LINE_MAX];
    int pointIndex = 0;
    while(fgets(line, LINE_MAX, input)) {
        int y = pointIndex / initialWidth;
        for (int x = 0; x < initialWidth; x++) {
            Point *p = &grid[pointIndex];
            p->x = x;
            p->y = y;

            if (line[x] == '#') {
                p->isGalaxy = true;
                emptyLine[y] = false; 
                galaxiesCount++;
            }

            pointIndex++;
        }
    }
    fclose(input);

    for (int i = 0; i < initialWidth; i++) {
        for (int j = 0; j < initialHeight; j++) {
            if (grid[j * initialWidth + i].isGalaxy) {
                emptyCol[i] = false;
            }
        }
    }

    Point *galaxies[galaxiesCount];
    int galaxyIdx = 0;
    for (int i = 0, offsetY = 0; i < initialHeight; i++) {
        if (emptyLine[i]) {
            offsetY++;
            continue;
        }

        int offsetX = 0;
        for (int j = 0; j < initialWidth; j++) {
            if (emptyCol[j]) {
                offsetX++;
                continue;
            }
            
            int idx = i * initialWidth + j;
            if (grid[idx].isGalaxy) {
                Point *p = &grid[idx]; 
                p->x += offsetX * 1000000 - offsetX;
                p->y += offsetY * 1000000 - offsetY;
                galaxies[galaxyIdx++] = &grid[idx]; 
            }
        }
    }

    uint64_t ans = 0;
    for (int i = 0; i < galaxiesCount; i++) {
        for (int j = i; j < galaxiesCount; j++) {
            if (i == j) 
                continue;
            
            Point p1 = *galaxies[i];
            Point p2 = *galaxies[j];
            int64_t diffX = p1.x - p2.x;
            int64_t diffY = p1.y - p2.y;
            uint64_t manhattanDistance = llabs(diffX) + llabs(diffY);
            ans += manhattanDistance;
        }
    }

    printf("ans: %lld\n", ans);
    return 0;
}
