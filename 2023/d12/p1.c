#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

#define FILE_NAME "input.txt"
#define LINE_MAX 65536

uint64_t search(const char *arrangement, size_t arrangeLen, uint64_t sizes[], size_t sizesLen) {
    if (arrangeLen == 0 && sizesLen == 0) return 1;
    if (sizesLen == 0) return strchr(arrangement, '#') ? 0 : 1;
    if (arrangeLen == 0) return 0;

    uint64_t requiredTrailing = sizes[0];

    size_t dotResult = (arrangement[0] == '.' || arrangement[0] == '?') ?
        search(arrangement + 1, arrangeLen - 1, sizes, sizesLen) : 0;

    size_t hashResult = 0;
    if (arrangement[0] == '#' || arrangement[0] == '?') {
        if (requiredTrailing <= arrangeLen &&
            strspn(arrangement, "#?") >= requiredTrailing &&
            (requiredTrailing == arrangeLen || arrangement[requiredTrailing] != '#')) {
            
            size_t skip = (sizesLen > 1) ? 1 : 0;
            hashResult = search(arrangement + requiredTrailing + skip,
                                arrangeLen - requiredTrailing - skip,
                                sizes + 1, sizesLen - 1);
        }
    }

    return dotResult + hashResult;
}

void toUInt64Arr (char **toks, uint64_t *out, size_t len) {
    for (size_t i = 0; i < len; i++) {
        unsigned long val = strtoul(toks[i], NULL, 10);
        if (val > UINT64_MAX) {
            fprintf(stderr, "Value out of range for uint64_t: %lu\n", val);
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

        size_t tokensCount = 0;
        char *tok = toks[tokensCount];
        for (; tok != NULL; tok = toks[++tokensCount]);

        uint64_t sizes[tokensCount];
        toUInt64Arr(toks, sizes, tokensCount);

        ans += search(arrangement, strlen(arrangement), sizes, tokensCount); 
        free(toks);
    }
    fclose(input);

    printf("ans: %llu\n", ans);
    return 0;
}
