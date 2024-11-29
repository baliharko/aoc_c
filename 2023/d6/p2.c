#include "str.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 65536

void removeWhitespace(char *line) {
    char *read = line, *write = line;
    while (*read) {
        if (!isspace((unsigned char)*read)) {
            *write++ = *read;
        }
        read++;
    }
    *write = '\0'; 
}

void parseInput(int64_t *time, int64_t *distance, FILE *input) {
    char line[LINE_MAX];
    fgets(line, LINE_MAX, input);
    removeWhitespace(line);
    char *pos = line;
    pos += indexof(line, ":") + 1;
    *time = atol(pos);

    fgets(line, LINE_MAX, input);
    removeWhitespace(line);
    pos = line;
    pos += indexof(line, ":") + 1;
    *distance = atol(pos);
}

int main(void) {
    FILE *input = fopen("2023/d6/input.txt", "r");
    if (input == NULL) {
        perror("Error opening file");
        return 1;
    }

    int64_t time;
    int64_t distance;
    parseInput(&time, &distance, input);
    fclose(input);

    int64_t ans = 0;
    int speed = 0;
    while (time > 0) {
        int64_t result = speed++ * time--;
        if (result >= distance) ans++;
    }

    printf("ans: %lld\n", ans);
    return 0;
}
