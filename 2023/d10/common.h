#pragma once

#include <stdbool.h>
#include <stdio.h>

#define LINE_MAX 65536
#define OFFSET(width) ((int[]){(-width), (1), (width), (-1),})

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
    int loopPosition; // amount of steps taken in a loop going in one direction
} Node;

void getInputDimensions(FILE *f, int *width, int *height);

void initNode(Node* n);

bool outOfBounds(Point *p, enum Direction dir, int width, int height);

void setNodes(Node *nodes, Point *points, int width, int height);

bool connects(Point *p1, Point *p2, enum Direction dir);

void dfs(Node *n, bool visited[]);

void calculateNodePositions(Node *start, int size);
