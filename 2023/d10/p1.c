#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "math.h"
#include "queue.h"

#define LINE_MAX 65536
#define FILE_NAME "input.txt"
#define OFFSET(a) ((int[]){(-a), (1), (a), (-1),})

enum Direction {
    N = 0,
    E,
    S,
    W,
};

typedef struct {
    char c;
    int x;
    int y;
} Point;

typedef struct Node {
    Point *p;
    struct Node* neighbours[4];
    int idx;
    int loopPosition;
} Node;

void initNode(Node* n) {
    n->p = NULL;
    n->idx = 0;
    n->loopPosition = -1;
    for (int i = 0; i < W + 1; i++) {
        n->neighbours[i] = NULL; 
    }
}

bool outOfBounds(Point *p, enum Direction dir, int size) {
    bool isAtLineEnd = p->x == size - 1;
    bool isAtLineBeginning = p->x == 0;
    bool isAtTop = p->y == 0;
    bool isAtBottom = p->y == size - 1;

    return (isAtLineEnd && dir == E) 
        || (isAtLineBeginning && dir == W)
        || (isAtTop && dir == N)
        || (isAtBottom && dir == S);
}

void setNodes(Node *nodes, Point *points, int size) {
    for (int i = 0; i < size * size; i++) {
        Node *n = &nodes[i];
        n->p = &points[i];
        n->idx = i;
        for (int j = 0; j <= W; j++) {
            if (outOfBounds(n->p, j, size)) 
                continue;

            int neighbourPos = i + OFFSET(size)[j];
            if (neighbourPos >= 0 && neighbourPos < size * size) {
                n->neighbours[j] = &nodes[neighbourPos];
            }
        }
    }
}

int idxof(const char *haystack, char c) {
    int idx = -1;
    size_t len = strlen(haystack);
    for (size_t i = 0; i < len; i++) {
        if (haystack[i] == c) {
            idx = i;
            break;
        }
    }
    return idx;
}

bool connects(Point *p1, Point *p2, enum Direction dir) {
    static const char *n = "|LJ";
    static const char *e = "-LF";
    static const char *s = "|F7";
    static const char *w = "-7J";

    if ((p1->c == 'S' && p2->c != '.') || (p2->c == 'S' && p1->c != '.')) {
        return true;
    }

    if (p1 == NULL || p2 == NULL) 
        return false;

    switch(dir) {
        case N:
            if (idxof(n, p1->c) >= 0 && idxof(s, p2->c) >= 0) return true;
            break;
        case E:
            if (idxof(e, p1->c) >= 0 && idxof(w, p2->c) >= 0) return true;
            break;
        case S:
            if (idxof(s, p1->c) >= 0 && idxof(n, p2->c) >= 0) return true;
            break;
        case W:
            if (idxof(w, p1->c) >= 0 && idxof(e, p2->c) >= 0) return true;
            break;
        default:
            return false;
            break;
    }

    return false;
}

void bfs(bool *visited, Queue *q) {
    while(q->count != 0) {
        Node *n = NULL;
        dequeue(q, &n);

        if (visited[n->idx]) 
            continue;

        visited[n->idx] = true;
        for (int i = 0; i <= W; i++) {
            Node *nb = n->neighbours[i];
            if (nb && nb->p && connects(n->p, nb->p, i) && !visited[nb->idx]) {
                nb->loopPosition = n->loopPosition + 1;
                enqueue(q, &nb);
            }
        }
    } 
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

void calculateLoopLength(Node *start, int size) {
    bool visited[size];
    for (int i = 0; i < size; i++) {
        visited[i] = false;
    }

    // Queue q;
    // initQueue(&q, sizeof(Node*));

    start->loopPosition = 0;

    // enqueue(&q, &start);

    // should do DFS to find which is the valid path and THEN calculate the distance...

    /*
        * DFS to find loop
        * Use queue (BFS style) to check distance of loop start and return point to find furthest point.
        (or divide total distance by 2...)
    */

    // bfs(visited, &q);

    dfs(start, visited);
}

int main(void) {
    FILE *input = fopen("2023/d10/" FILE_NAME, "r");
    if (input == NULL) {
        perror("Error opening file. Exiting.");
        return -1;
    }


    int size = strcmp(FILE_NAME, "example.txt") == 0 ? 5 : 140;
    Point *points = malloc(sizeof(Point) * size * size);
    for (int i = 0; i < size * size; i++) {
        points[i].c = 0;
        points[i].x = 0;
        points[i].y = 0;
    }

    int startIdx = -1;
    int y = 0;
    char line[LINE_MAX];
    while(fgets(line, LINE_MAX, input)) {
        for (int x = 0; x < size; x++) {
            Point *p = &points[size * y + x];
            p->c = line[x];
            p->x = x;
            p->y = y;

            if (p->c == 'S') {
                startIdx = y * size + x;
            }
        }
        y++;
    } 

    Node *nodes = malloc(sizeof(Node) * size * size);
    for (int i = 0; i < size * size; i++) {
        initNode(&nodes[i]);
    }

    setNodes(nodes, points, size);
    calculateLoopLength(&nodes[startIdx], size * size);

    int ans = 0;
    for (int i = 0; i < size * size; i++) {
        Node *n = &nodes[i];
        if (n->loopPosition >= 0) {
            ans = max(ans, n->loopPosition);
        }
    }

    ans = (ans + 1) / 2;
    printf("ans: %d\n", ans);

    assert(ans == 6923);
    return 0;
}
