#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

#define LINE_BUFFER 10000

int main() {
    FILE* file = fopen("2023/d1/input.txt", "r");
    if(!file) {
        printf("Error opening file");
        return 1;
    }

    int line_count = count_lines(file);
    char nums[line_count][3];
    int nums_idx = 0;
    char line[LINE_BUFFER];
    while(fgets(line, sizeof(line), file)) {
        int len = strlen(line);
        int is_first_num_set = 0;
        char last_char;
        for(int i = 0; i < len; i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                if (is_first_num_set == 0) {
                    nums[nums_idx][0] = line[i];
                    is_first_num_set = 1;
                }
                last_char = line[i];
            }
        }
        nums[nums_idx][1] = last_char;
        nums[nums_idx++][2] = '\0';
    }

    int ans = 0;
    for(int i = 0; i < line_count; i++) {
        ans += atoi(nums[i]);
    }
    
    printf("ans: %d\n", ans);
    fclose(file);
    return 0;
}

