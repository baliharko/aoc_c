#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "common.h"
#include "math.h"

#define FILE_NAME "input.txt"

int main(void) {
    FILE *input = fopen("2023/d10/" FILE_NAME, "r");
    if (input == NULL) {
        perror("Error opening file. Exiting.");
        return -1;
    }

    int width = 0, height = 0;
    getInputDimensions(input, &width, &height);

    Point *points = malloc(sizeof(Point) * width * height);
    for (int i = 0; i < width * height; i++) {
        points[i].c = 0;
        points[i].x = 0;
        points[i].y = 0;
    }

    int startIdx = -1;
    int y = 0;
    char line[LINE_MAX];
    while(fgets(line, LINE_MAX, input)) {
        for (int x = 0; x < width; x++) {
            Point *p = &points[width * y + x];
            p->c = line[x];
            p->x = x;
            p->y = y;

            if (p->c == 'S') {
                startIdx = y * width + x;
            }
        }
        y++;
    } 

    Node *nodes = malloc(sizeof(Node) * width * height);
    for (int i = 0; i < width * height; i++) {
        initNode(&nodes[i]);
    }

    setNodes(nodes, points, width, height);
    calculateNodePositions(&nodes[startIdx], width * height);

    int ans = 0;
    for (int i = 0; i < width * height; i++) {
        Node *n = &nodes[i];
        if (n->loopPosition >= 0) {
            ans = max(ans, n->loopPosition);
        }
    }

    ans = (ans + 1) / 2; // +1 since loop starts from 0
    printf("ans: %d\n", ans);

    assert(ans == 6923);
    return 0;
}
