#include "../../util/input.h"
#include <stdio.h>
#include <string.h>
#include "common.h"

#define LINE_LENGTH 140
#define MAX_CHARS 65536 // 16 bit integer max number

int main(void) {
    const char* input_str = input_as_cont_string("2023/d3/input.txt", MAX_CHARS);
    int input_len = strlen(input_str);

    int sum = 0;
    int i = 0;
    char token[LINE_LENGTH] = { '\0' };
    int tokenIdx = 0;
    while (i < input_len) {
        if (input_str[i] >= '0' && input_str[i] <= '9')
            token[tokenIdx++] = input_str[i];
        else {
            if (tokenIdx > 0) {
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
        }

        i++;
    }

    printf("sum: %d\n", sum);
    return 0;
}

