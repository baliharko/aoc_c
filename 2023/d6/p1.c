#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 65536

void parseLines(long boats[][2], FILE *input) {
    char line[LINE_MAX];
    int lineIdx = 0;
    while(fgets(line, LINE_MAX, input)) {
        const char *pos = line;
        int numIdx = 0;
        while (*pos ) {
            if (*pos > '9' || *pos < '0') {
                pos++;
                continue;
            }

            char *end;
            long num = strtol(pos, &end, 10);

            if (pos == end) break;

            boats[numIdx][lineIdx] = num; 
            pos = end;
            numIdx++;
        }
        lineIdx++;
    }
}

long countTokens(char *line) {
    long tokens = 0;
    char *token;
    token = strtok(line, " ");
    while (token != NULL) {
        tokens++;
        token = strtok(NULL, " ");
    }

    return tokens;
}

int main(void) {
    FILE *input = fopen("2023/d6/input.txt", "r");
    if (input == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[LINE_MAX];
    fgets(line, LINE_MAX, input);
    int nums = countTokens(line) - 1; 
    rewind(input);

    long boats[nums][2];
    parseLines(boats, input);

    int64_t ans = 1;
    for (int i = 0; i < nums; i++) {
        int ways = 0;
        int time = boats[i][0];
        int distance = boats[i][1];
        int speed = 0;
        while (time >= 0) {
            int result = speed++ * time--;
            if (result > distance) ways++;
        }

        ans *= ways;
    }

    printf("ans: %lld\n", ans);
    fclose(input);
    return 0;
}
