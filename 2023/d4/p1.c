#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../util/str.h"

#define MAX_CHARS 65536
#define NUM_MAX_VALUE 100

void populate_array(const char* line, int start_index, int end_index, char* out);

int main(void) {
    FILE* input = fopen("2023/d4/input.txt", "r"); 
    if (input == NULL) {
        printf("Error opening file.");
        return 1;
    }

    unsigned int points_sum = 0;

    char line[MAX_CHARS];
    while(fgets(line, MAX_CHARS, input)) {
        int colon_index = indexof(line, ":");
        int pipe_index = indexof(line, "|");
        int line_len = indexof(line, "\n") + 1;

        char numbers[NUM_MAX_VALUE] = { 0 };
        char winning_numbers[NUM_MAX_VALUE] = { 0 };
        populate_array(line, colon_index, pipe_index, numbers);
        populate_array(line, pipe_index + 1, line_len, winning_numbers);

        unsigned int line_sum = 0;
        for (int i = 0; i < NUM_MAX_VALUE; i++) {
            if (!(numbers[i] == 1 && winning_numbers[i] == 1))
                continue;

            line_sum = line_sum == 0 ? 1 : line_sum << 1;
        }

        points_sum += line_sum;
    }

    printf("sum: %d\n", points_sum);
    return 0;
}

void populate_array(const char* line, int start_index, int end_index, char* out) {
    char token[3]; // since max value of numbers are 100 ("100")
    int token_index = 0;
    for (int i = start_index; i < end_index; i++) {
        if (is_digit(line[i])) {
            token[token_index++] = line[i];
        } else if (token_index > 0) {
            int value = atoi(token);
            out[value] = 1;
            token_index = 0;
            memset(&token, 0, sizeof(token));
        }
    }
}
