#include "../../util/input.h"
#include <stdio.h>
#include <string.h>
#include "common.h"

#define MAX_CHARS 65336 // 16 bit integer max value

int is_symbol(const char c);

int main(void) {
    const char* input_str = input_as_cont_string("2023/d3/input.txt", MAX_CHARS);
    const int input_len = strlen(input_str);

    int sum = 0;
    int i = 0;
    char token[TOKEN_MAX] = { '\0' };
    int tokenIdx = 0;
    while (i < input_len) {
        if (is_digit(input_str[i]))
            token[tokenIdx++] = input_str[i];
        else if (tokenIdx > 0){
            for (int j = i - tokenIdx - 1; j < i + 1; j++) {
                if (j < 0) continue;
                if (j % LINE_LENGTH == 0 || j % LINE_LENGTH == 0) continue;

                if (is_symbol(input_str[j]))
                    sum += atoi(token);

                if (j > LINE_LENGTH && is_symbol(input_str[j - LINE_LENGTH]))
                    sum += atoi(token);

                if (j + LINE_LENGTH < input_len && is_symbol(input_str[j + LINE_LENGTH]))
                    sum += atoi(token);
            }

            memset(token, '\0', sizeof(token));
            tokenIdx = 0;
        }

        i++;
    }

    printf("sum: %d\n", sum);
    return 0;
}

int is_symbol(const char c) {
    return (c > '9' || c < '0') && c != '.';
}

