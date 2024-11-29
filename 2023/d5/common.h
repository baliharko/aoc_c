#pragma once

#include <stdint.h>

#define LINE_LIMIT 65536
#define MAPS_AMT 7

typedef struct {
    int64_t first;
    int64_t last;
} Range;

typedef struct MapRange {
    Range range;
    int64_t offset;
} MapRange;
