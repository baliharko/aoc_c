#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "dynarray.h"
#include "str.h"
#include "macro.h"

#define MAX_CHARS 65536
#define MAPS_AMT 7

typedef struct {
    int destinationRangeStart;
    int sourceRangeStart;
    int rangeLength;
} Range;

typedef struct {
    DynArray* ranges;
} ResourceMap;

ResourceMap* newResourceMap() {
    ResourceMap* map = malloc(sizeof(ResourceMap));
    if (map == NULL) {
        printf("Failed to allocate memory for new ResourceMap\n");
        return NULL;
    }

    DynArray* r = malloc(sizeof(DynArray));
    if (r == NULL) {
        printf("Failed to allocate memory for new DynArray\n");
        return NULL;
    }

    init_dynarray(r);
    map->ranges = r;
    return map;
}

void getSeeds(const char* line, DynArray* seeds) {
    const char* pos = line;
    pos += strlen("seeds: ");
    while (*pos) {
        char* end;
        uint64_t seed = strtol(pos, &end, 10);

        if (pos == end) break;

        push_back(seeds, &seed, sizeof(long));
        pos = end;
        pos += strspn(pos, " ");
    }
}

int mapSeed(ResourceMap* map, int seed) {
    int rangesLen = map->ranges->size;
    for (int i = 0; i < rangesLen; i++) {
        Range* r = element_at(map->ranges, i);
        if (seed < r->sourceRangeStart) continue;

        if (seed >= r->sourceRangeStart && seed < r->sourceRangeStart + r->rangeLength) {
            int offset = seed - r->sourceRangeStart;
            return r->destinationRangeStart + offset;
        }
    }

    return seed; 
}

void printRange(Range* range) {
    printf("%d %d %d\n", range->destinationRangeStart, range->sourceRangeStart, range->rangeLength);
}

int main(void) {
    FILE* input = fopen("2023/d5/input.txt", "r");
    if (input == NULL) {
        printf("Error opening file.");
        return 1;
    }

    ResourceMap maps[MAPS_AMT];
    for (int i = 0; i < MAPS_AMT; i++) {
        maps[i] = *newResourceMap();
    }

    DynArray seeds;
    init_dynarray(&seeds);

    int mapIdx = -1;
    char line[MAX_CHARS];
    int firstLine = true;
    while(fgets(line, MAX_CHARS, input)) {
        if (firstLine) {
            firstLine = false;
            getSeeds(line, &seeds);
            continue;
        }

        if (line[0] == '\n') 
            continue;

        if (indexof(line, "-to-") > 0) {
            mapIdx++;
            continue;
        }

        Range range;
        if (sscanf(line, "%d %d %d", &range.destinationRangeStart, &range.sourceRangeStart, &range.rangeLength)) {
            push_back(maps[mapIdx].ranges, &range, sizeof(Range));
        }
    }

    uint64_t ans = ULONG_MAX;
    for (int i = 0; i < (int)seeds.size; i++) {
        unsigned long seed = *(int*)element_at(&seeds, i);
        unsigned long mapped = seed;
        for (int j = 0; j < MAPS_AMT; j++) {
            mapped = mapSeed(&maps[j], mapped);
        }

        ans = MIN(ans, mapped);
    }
    printf("%llu\n", ans);

    return 0;
}

