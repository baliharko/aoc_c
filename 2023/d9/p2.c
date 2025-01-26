#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "str.h"
#include "common.h"

int getSequence(int seq[], size_t size) {
    if (all(seq, size, 0)) {
        return 0;
    }

    int out[size -1];
    for (size_t i = size - 1; i > 0; i--) {
        int a = seq[i];
        int b = seq[i - 1];

        out[i - 1] = a - b;
    }

    return seq[0] - getSequence(out, size - 1);
}

int main(void) {
    FILE *input = fopen("2023/d9/input.txt", "r");
    if (input == NULL) {
        perror("Error reading file. Exiting.");
            return -1;
    }

    char line[LINE_MAX];
    bool firstLine = true;
    int tokensCount = 0;
    int ans = 0;
    while(fgets(line, LINE_MAX, input)) {
        if (firstLine) {
            tokensCount = countTokens(line);
            firstLine = false;
        }

        char **toks = tokens(line, " ");
        int seq[tokensCount];
        for (int i = 0; i < tokensCount; i++) {
            seq[i] = atoi(toks[i]);
        }

        int predict = getSequence(seq, tokensCount);
        ans += predict;
    }

    fclose(input);
    printf("ans: %d\n", ans);
    return 0;
}
