#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"
#include "hashmap.h"

#define FILE_NAME "input.txt"
#define LINE_MAX 65536
#define MAX_KEY_SIZE 1024

typedef HashMap Cache;

typedef struct {
    char *arrangement;
    size_t arrangementLen;
    uint64_t *sizes;
    size_t sizesLen;
} CacheKey;

// wrap because 0 is falsy when checking results
typedef struct { 
    uint64_t value;
} CacheValue;

bool serializeCacheKey(const CacheKey *key, size_t keySize, void* buffer, size_t bufferSize) {
    if (keySize > bufferSize) {
        return false;
    }

    memcpy(buffer, key, sizeof(CacheKey));

    char *arrangementDest = (char*)buffer + sizeof(CacheKey);
    memcpy(arrangementDest, key->arrangement, key->arrangementLen);

    uint64_t *sizesDest = (uint64_t*)(arrangementDest + key->arrangementLen);
    memcpy(sizesDest, key->sizes, key->sizesLen * sizeof(uint64_t));

    ((CacheKey*)buffer)->arrangement = arrangementDest;
    ((CacheKey*)buffer)->sizes = sizesDest;
    return true;
}

uint64_t search(char *arrangement, size_t arrangeLen, uint64_t sizes[], size_t sizesLen, Cache *cache) {
    size_t entrySize = sizeof(CacheKey) + sizesLen * sizeof(uint64_t) + arrangeLen;
    CacheKey ce = {
        .arrangement = arrangement,
        .arrangementLen = arrangeLen,
        .sizes = sizesLen > 0 ? sizes : NULL,
        .sizesLen = sizesLen        
    };

    unsigned char keyBuffer[MAX_KEY_SIZE] = { -1 };
    if (!serializeCacheKey(&ce, entrySize, keyBuffer, sizeof(keyBuffer))) {
        perror("Error serializing key.\n");
    }

    CacheValue *cached = HMGet(cache, keyBuffer, entrySize);
    if (cached != NULL) {
        return cached->value;
    }

    if (arrangeLen == 0 && sizesLen == 0) return 1;
    if (sizesLen == 0) return strchr(arrangement, '#') ? 0 : 1;
    if (arrangeLen == 0) return 0;

    uint64_t requiredTrailing = sizes[0];

    size_t dotResult = (arrangement[0] == '.' || arrangement[0] == '?') ?
        search(arrangement + 1, arrangeLen - 1, sizes, sizesLen, cache) : 0;

    size_t hashResult = 0;
    if (arrangement[0] == '#' || arrangement[0] == '?') {
        if (requiredTrailing <= arrangeLen &&
            strspn(arrangement, "#?") >= requiredTrailing &&
            (requiredTrailing == arrangeLen || arrangement[requiredTrailing] != '#')) {
            
            size_t skip = (sizesLen > 1 && arrangeLen != requiredTrailing) ? 1 : 0;

            hashResult = search(arrangement + requiredTrailing + skip,
                                arrangeLen - requiredTrailing - skip,
                                sizes + 1, sizesLen - 1, cache);
        }
    }

    uint64_t result = dotResult + hashResult;
    CacheValue cv = { .value = result };
    HMSet(cache, keyBuffer, entrySize, &cv, sizeof(CacheValue));
    return result;
}

void toUInt64Arr (char **toks, uint64_t *out, size_t len) {
    for (size_t i = 0; i < len; i++) {
        uint64_t val = strtoull(toks[i], NULL, 10);
        if (val > UINT64_MAX) {
            fprintf(stderr, "Value out of range for uint64_t: %llu\n", val);
            exit(EXIT_FAILURE);
        }

        out[i] = val;
    }
}

int main(void) {
    FILE *input = fopen("2023/d12/" FILE_NAME, "r");
    if (!input) {
        perror("Error opening file, exiting.\n");
    }

    Cache *cache = HMCreate();
    
    uint64_t ans = 0; 
    char line[LINE_MAX];
    while (fgets(line, LINE_MAX, input)) {
        char *groups = line + indexof(line, " ") + 1;
        line[indexof_c(line, ' ')] = '\0';
        char *arrangement = line;

        char **toks = tokens(groups, ",");
        if (!toks) {
            printf("Error getting tokens. Exiting.\n");
            return 1;
        }

        size_t arrangementLen = strlen(arrangement);
        char unfoldedArrangement[arrangementLen * 5 + 6];
        unfoldedArrangement[0] = '\0';
        for (int i = 0; i < 5; i++) {
            strcat(unfoldedArrangement, arrangement);

            if (i != 4)
                strcat(unfoldedArrangement, "?");
        }

        size_t tokensCount = 0;
        char *tok = toks[tokensCount];
        for (; tok != NULL; tok = toks[++tokensCount]);

        uint64_t sizes[tokensCount];
        toUInt64Arr(toks, sizes, tokensCount);
        uint64_t unfoldedSizes[tokensCount * 5];
        for (int i = 0; i < 5; i++) {
            memcpy(unfoldedSizes + (i * tokensCount), sizes, tokensCount * sizeof(uint64_t));
        }

        ans += search(unfoldedArrangement, strlen(unfoldedArrangement), unfoldedSizes, tokensCount * 5, cache); 
        free(toks);
    }
    fclose(input);

    HMDestroy(cache);
    printf("ans: %llu\n", ans);
    return 0;
}
