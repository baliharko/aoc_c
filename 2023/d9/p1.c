#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "str.h"
    
#define LINE_MAX 65536

bool all(int arr[], size_t size, int compare) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] != compare) 
            return false;
    }

    return true;
}

int getSequence(int seq[], size_t size) {
    if (all(seq, size, 0)) {
        return 0;
    }

    int out[size -1];
    for (size_t i = 0; i < size - 1; i++) {
        int a = seq[i];
        int b = seq[i + 1];

        out[i] = b - a;
    }

    return seq[size - 1] + getSequence(out, size - 1);
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