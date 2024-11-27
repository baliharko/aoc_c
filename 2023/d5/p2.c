#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "dynarray.h"
#include "str.h"
#include "macro.h"

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

void printRange(Range *r) {
    printf("{ %lld, %lld }", r->first, r->last);
}

void getSeedRanges(const char* line, DynArray* seedRanges) {
    const char* pos = line;
    pos += strlen("seeds: ");
    char* end;

    while (*pos != '\n') {
        uint64_t start = strtol(pos, &end, 10);
        pos = end;
        pos += strspn(pos, " ");

        uint64_t length = strtol(pos, &end, 10);
        Range sr;
        sr.first = start;
        sr.last = start + length - 1;
        push_back(seedRanges, &sr, sizeof(Range));

        pos = end;
        pos += strspn(pos, " ");
    }
}

int main(void) {
    FILE* input = fopen("2023/d5/input.txt", "r");
    if (input == NULL) {
        printf("Error opening file.");
        return 1;
    }

    DynArray maps[MAPS_AMT];
    for (int i = 0; i < MAPS_AMT; i++) {
        init_dynarray(&maps[i]);
    }

    DynArray seedRanges;
    init_dynarray(&seedRanges);

    char line[LINE_LIMIT];
    fgets(line, LINE_LIMIT, input);
    getSeedRanges(line, &seedRanges);

    int mapIdx = -1;
    while(fgets(line, LINE_LIMIT, input)) {

        if (line[0] == '\n') continue;

        if (indexof(line, "-to-") > 0) {
            mapIdx++;
            continue;
        }

        int64_t dest;
        int64_t source;
        int64_t length;
        if (sscanf(line, "%lld %lld %lld", &dest, &source, &length) == 3) {
            MapRange mapRange;
            Range range;
            range.first = source;
            range.last = source + length - 1;
            mapRange.range = range;
            mapRange.offset = dest - source; 
            push_back(&maps[mapIdx], &mapRange, sizeof(MapRange));
        }
    }

    for (int i = 0; i < MAPS_AMT; i++) {
        DynArray mappedRanges;
        init_dynarray(&mappedRanges);
        DynArray map = maps[i];
        while (seedRanges.size > 0) {
            Range seedRange;
            pop(&seedRanges, &seedRange, sizeof(Range));
            bool mapped = false;
            for (size_t k = 0; k < map.size; k++) {
                MapRange *mr = element_at(&map, k);
                if (seedRange.first > mr->range.last || seedRange.last < mr->range.first) {
                    continue;
                }

                mapped = true;
                int64_t overlapFirst = MAX(seedRange.first, mr->range.first);
                int64_t overlapLast = MIN(seedRange.last, mr->range.last);
                Range overlapRange;
                overlapRange.first = overlapFirst + mr->offset;
                overlapRange.last = overlapLast + mr->offset;
                push_back(&mappedRanges, &overlapRange, sizeof(Range));

                if (seedRange.first < overlapFirst) {
                    Range r;
                    r.first = seedRange.first;
                    r.last = overlapFirst - 1;
                    push_back(&seedRanges, &r, sizeof(Range));
                }

                if (seedRange.last > overlapLast) {
                    Range r;
                    r.first = overlapLast + 1;
                    r.last = seedRange.last;
                    push_back(&seedRanges, &r, sizeof(Range));
                }

                break;
            }

            if (!mapped) {
                push_back(&mappedRanges, &seedRange, sizeof(Range));
            }
        }

        DynArray temp = seedRanges;
        seedRanges = mappedRanges;
        mappedRanges = temp;
        destroy(&mappedRanges);
    }

    int64_t ans = INT64_MAX;
    for (size_t i = 0; i < seedRanges.size; i++) {
        Range *r = element_at(&seedRanges, i);
        ans = MIN(ans, r->first);
    }

    printf("ans: %lld\n", ans);

    destroy(&seedRanges);
    for (int i = 0; i < MAPS_AMT; i++) {
        destroy(&maps[i]);
    }
    return 0;
}

