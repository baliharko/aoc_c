#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define LINE_MAX 65536

typedef struct {
    bool isGalaxy;
    uint64_t x;
    uint64_t y;
} Point;

void getInputDimensions(FILE *f, int *width, int *height);
