#include <stdio.h>
#include <string.h>
#include "input.h"
#include "dynarray.h"
#include "common.h"
#include "str.h"

#define MAX_CHARS 65536 // 16 bit integer max value

typedef struct {
    int value;
    int start_index;
    int end_index;
} Value;

void parse_input(const char* input_str, const int input_len, DynArray* values, DynArray* star_indexes);

int main(void) {
    const char* INPUT_STR = input_as_cont_string("2023/d3/input.txt", MAX_CHARS);
    const int INPUT_LEN = strlen(INPUT_STR);

    DynArray values;
    DynArray star_indexes;
    init_dynarray(&values);
    init_dynarray(&star_indexes);

    parse_input(INPUT_STR, INPUT_LEN, &values, &star_indexes);

    int sum = 0;
    for (size_t i = 0; i < star_indexes.size; i++) {
        int star_line = *((int*)element_at(&star_indexes, i)) / LINE_LENGTH;
        int adjacent_values[5] = { 0 };
        int adjacent_vals_index = 0;
        for (size_t j = 0; j < values.size; j++) {
            Value* value = element_at(&values, j);
            int value_line = value->start_index / LINE_LENGTH;
            if (value_line < star_line - 1 || value_line > star_line + 1)
                continue;

            int star_index = *((int*)element_at(&star_indexes, i));
            if (value->start_index - 1 == star_index || value->end_index + 1 == star_index)
                adjacent_values[adjacent_vals_index++] = value->value;

            for (int k = value->start_index - 1; k <= value->end_index + 1; k++) {
                if (k < 0 || k > INPUT_LEN) continue;

                if (k - LINE_LENGTH == star_index || k + LINE_LENGTH == star_index)
                    adjacent_values[adjacent_vals_index++] = value->value;
            }
        }

        if (adjacent_vals_index == 2)
            sum += adjacent_values[0] * adjacent_values[1];

        memset(adjacent_values, 0, sizeof(adjacent_values));
        adjacent_vals_index = 0;
    }

    printf("sum: %d\n", sum);

    free((char*)INPUT_STR);
    INPUT_STR = NULL;
    return 0;
}

void parse_input(const char* input_str, const int input_len, DynArray* values, DynArray* star_indexes) {
    char token[TOKEN_MAX] = { '\0' };
    int token_index = 0;
    for (int i = 0; i < input_len; i++) {
        if (is_digit(input_str[i]))
            token[token_index++] = input_str[i];     
        else if (token_index > 0) {
            Value val = { .value = atoi(token), .start_index = i - token_index, .end_index = i - 1 };
            push_back(values, &val, sizeof(Value));
            token_index = 0;
            memset(token, '\0', sizeof(token));
        }

        if (input_str[i] == '*')
            push_back(star_indexes, &i, sizeof(int));
    }
}

