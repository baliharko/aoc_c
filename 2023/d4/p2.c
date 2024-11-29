#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "str.h"

void populate_array(const char* line, int start_index, int end_index, char* out);

int main(void) {
    FILE* input = fopen("2023/d4/input.txt", "r"); 
    if (input == NULL) {
        printf("Error opening file.");
        return 1;
    }

    int lines = count_lines(input);
    int cards[lines];
    for (int i = 0; i < lines; i++) 
        cards[i] = 1;

    char line[MAX_CHARS];
    unsigned int current_line = 0;
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

            line_sum++;
        }

        for (int i = 0; i < cards[current_line]; i++) {
            for (unsigned int j = current_line + 1; j < current_line + 1 + line_sum ; j++) {
                cards[j]++;
            }
        }

        current_line++;
    }

    unsigned int sum = 0;
    for (int i = 0; i < lines; i++) {
        sum += cards[i];
    }

    printf("sum: %d\n", sum);
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
