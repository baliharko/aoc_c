#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "common.h"
#include "math.h"

#define FILE_NAME "input.txt"

void getRouteNodes(Node *route[], int len, int width, int height) { 
    for (int i = len; i > 0; i--) {
        Node *n = route[i];
        for (int dir = N; dir <= W; dir++) {
            Node *nb = n->neighbours[dir];

            if (!nb || outOfBounds(n->p, dir, width, height))
                continue;

            if (connects(n->p, nb->p, dir) && nb->loopPosition == n->loopPosition - 1) {
                route[i - 1] = nb;
                break;
            }
        } 
    }
}

int areaByShoelace(Node* route[], int length, int width, int height) {
    int area = 0;
    for (int i = 0; i < length; i++) {
        int j = mod(i + 1, length);
        Node n1 = *route[i];
        Node n2 = *route[j];
        int y1 = n1.idx / height;
        int x1 = mod(n1.idx, width);
        int y2 = n2.idx / height;
        int x2 = mod(n2.idx, width);

        area += (x1 * y2) - (y1 * x2);
    }

    return abs(area) / 2;
}

int main(void) {
    FILE *input = fopen("2023/d10/" FILE_NAME, "r");
    if (input == NULL) {
        perror("Error opening file. Exiting.\n");
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
    while (fgets(line, LINE_MAX, input)) {
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

    int maxSteps = 0;
    for (int i = 0; i < width * height; i++) {
        Node *n = &nodes[i];
        maxSteps = max(n->loopPosition, maxSteps);
    }

    Node *start = &nodes[startIdx];
    Node *last = start;
    for (int i = N; i <= W; i++) {
        Node *nb = start->neighbours[i];
        if (nb && nb->p && connects(start->p, nb->p, i) && nb->loopPosition > last->loopPosition) {
            last = start->neighbours[i];
        }
    }

    Node *route[maxSteps + 1];
    route[maxSteps] = last;
    getRouteNodes(route, maxSteps, width, height); 

    // get area using shoelace formula
    int area = areaByShoelace(route, maxSteps, width, height);

    // get interior points using picks theorem (i = A - b/2 - h + 1)
    int ans = area - ((maxSteps + 1) / 2) + 1;
    printf("%u\n", ans);
 
    assert(ans == 529);
    return 0;
}
