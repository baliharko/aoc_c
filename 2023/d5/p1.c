#include "dynarray.h"
#include "str.h"
#include <stdbool.h>
#include <stdio.h>
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

void getSeeds(const char* line, DynArray* seeds) {
    const char* pos = line;
    pos += strlen("seeds: ");
    while (*pos) {
        char *end;
        int64_t seed = strtol(pos, &end, 10);

        if (pos == end) break;

        push_back(seeds, &seed, sizeof(int64_t));
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

    DynArray maps[7];
    for (int i = 0; i < MAPS_AMT; i++) {
        init_dynarray(&maps[i]);
    }

    DynArray seeds;
    init_dynarray(&seeds);

    char line[LINE_LIMIT];

    // get the first line
    fgets(line, LINE_LIMIT, input);
    getSeeds(line, &seeds);

    // get the rest
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
        DynArray map = maps[i];
        for (size_t j = 0; j < seeds.size; j++) {
            int64_t *seed = element_at(&seeds, j);
            for (size_t k = 0; k < map.size; k++) {
                MapRange *mr = element_at(&map, k);
                if (*seed >= mr->range.first && *seed <= mr->range.last) {
                    *seed = *seed + mr->offset;
                    break;
                }
            }    
        }
    }

    int64_t ans = INT64_MAX;
    for (size_t i = 0; i < seeds.size; i++) {
        int64_t *seed = element_at(&seeds, i); 
        ans = MIN(ans, *seed);
    }

    printf("ans: %lld\n", ans);

    destroy(&seeds);
    for (int i = 0; i < MAPS_AMT; i++) {
        destroy(&maps[i]);
    }

    return 0;
}
