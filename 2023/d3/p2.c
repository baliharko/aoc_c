#include <stdio.h>
#include <string.h>
#include "../../util/input.h"
#include "../../util/dynarray.h"
#include "common.h"


typedef struct {
    int value;
    int startIdx;
    int endIdx;
} Value;

int within_bounds(int i, Value* value);

int main(void) {
    const char* input_str = input_as_cont_string("2023/d3/input.txt", MAX_CHARS);
    const int input_len = strlen(input_str);

    DynArray values;
    init_dynarray(&values);

    char token[TOKEN_MAX] = { '\0' };
    int tokenIdx = 0;
    int starsIndexes[MAX_CHARS] = { 0 };
    int starsIdx = 0;
    for (int i = 0; i < input_len; i++) {
        if (is_digit(input_str[i]))
            token[tokenIdx++] = input_str[i];     
        else if (tokenIdx > 0) {
            Value val = { .value = atoi(token), .startIdx = i - tokenIdx, .endIdx = i - 1 };
            push_back(&values, &val, sizeof(Value));
            tokenIdx = 0;
            memset(token, '\0', sizeof(token));
        }

        if (input_str[i] == '*')
            starsIndexes[starsIdx++] = i;
    }

    int sum = 0;
    for (int i = 0; i < starsIdx; i++) {
        int star_line = starsIndexes[i] / LINE_LENGTH;
        int adjacent_values[5] = { 0 };
        int adjacent_vals_amt = 0;
        for (size_t j = 0; j < values.size; j++) {
            Value* value = element_at(&values, j);
            int value_line = value->startIdx / LINE_LENGTH;
            if (value_line < star_line - 1 || value_line > star_line + 1)
                continue;

            if (value->startIdx - 1 == starsIndexes[i] || value->endIdx + 1 == starsIndexes[i])
                adjacent_values[adjacent_vals_amt++] = value->value;

            for (int k = value->startIdx - 1; k <= value->endIdx + 1; k++) {
                if (k < 0 || k > input_len) continue;

                if (k - LINE_LENGTH == starsIndexes[i] || k + LINE_LENGTH == starsIndexes[i]) {
                    adjacent_values[adjacent_vals_amt++] = value->value;
                }
            }
        }

        if (adjacent_vals_amt == 2)
            sum += adjacent_values[0] * adjacent_values[1];

        memset(adjacent_values, 0, sizeof(adjacent_values));
        adjacent_vals_amt = 0;
    }

    printf("sum: %d\n", sum);
    return 0;
}

int within_bounds(int i, Value* value) {
    return i >= value->startIdx - 1 && i <= value->endIdx + 1;
}

