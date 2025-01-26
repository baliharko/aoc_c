#include <stddef.h>

#include "common.h"
#include "str.h"

void getInputDimensions(FILE *f, int *width, int *height) {
    char buffer[LINE_MAX];
    fgets(buffer, LINE_MAX, f);

    int w = 0;
    int i = 0;
    while (buffer[i] != '\n') {
        w++;
        i++;
    }
    *width = w;

    int h = 1;
    while (fgets(buffer, LINE_MAX, f)) {
        h++;  
    }
    *height = h;

    rewind(f);
}

void initNode(Node* n) {
    n->p = NULL;
    n->idx = 0;
    n->loopPosition = -1;
    for (int i = 0; i < W + 1; i++) {
        n->neighbours[i] = NULL; 
    }
}

bool outOfBounds(Point *p, enum Direction dir, int width, int height) {
    bool isAtLineEnd = p->x == width - 1;
    bool isAtLineBeginning = p->x == 0;
    bool isAtTop = p->y == 0;
    bool isAtBottom = p->y == height - 1;

    return (isAtLineEnd && dir == E) 
        || (isAtLineBeginning && dir == W)
        || (isAtTop && dir == N)
        || (isAtBottom && dir == S);
}

void setNodes(Node *nodes, Point *points, int width, int height) {
    for (int i = 0; i < width * height; i++) {
        Node *n = &nodes[i];
        n->p = &points[i];
        n->idx = i;
        for (int j = 0; j <= W; j++) {
            if (outOfBounds(n->p, j, width, height)) 
                continue;

            int neighbourPos = i + OFFSET(width)[j];
            if (neighbourPos >= 0 && neighbourPos < width * height) {
                n->neighbours[j] = &nodes[neighbourPos];
            }
        }
    }
}

bool connects(Point *p1, Point *p2, enum Direction dir) {
    static const char *n = "|LJ";
    static const char *e = "-LF";
    static const char *s = "|F7";
    static const char *w = "-7J";

    if ((p1->c == 'S' && p2->c != '.') || (p2->c == 'S' && p1->c != '.')) {
        return true;
    }

    switch(dir) {
        case N:
            if (indexof_c(n, p1->c) >= 0 && indexof_c(s, p2->c) >= 0) return true;
            break;
        case E:
            if (indexof_c(e, p1->c) >= 0 && indexof_c(w, p2->c) >= 0) return true;
            break;
        case S:
            if (indexof_c(s, p1->c) >= 0 && indexof_c(n, p2->c) >= 0) return true;
            break;
        case W:
            if (indexof_c(w, p1->c) >= 0 && indexof_c(e, p2->c) >= 0) return true;
            break;
        default:
            return false;
            break;
    }

    return false;
}

void dfs(Node *n, bool visited[]) {
    visited[n->idx] = true;

    for (int i = N; i <= W; i++) {
        Node *nb = n->neighbours[i];

        if (nb && connects(n->p, nb->p, i) && !visited[nb->idx]) {
            nb->loopPosition = n->loopPosition + 1;
            dfs(nb, visited);
        }
    }
}

void calculateNodePositions(Node *start, int size) {
    bool visited[size];
    for (int i = 0; i < size; i++) {
        visited[i] = false;
    }

    start->loopPosition = 0;
    dfs(start, visited);
}

