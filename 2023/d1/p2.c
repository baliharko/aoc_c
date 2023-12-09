#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER 10000
#define NUM_WORDS_LENGTH 9

int count_lines(FILE* file);
int indexof(const char* haystack, const char* needle);

const char* const NUM_WORDS[NUM_WORDS_LENGTH] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };  
FILE* input;

int main() {
    input = fopen("2023/d1/input.txt", "r");
    if(!input) {
        printf("Error opening file");
        return 1;
    }

    int line_count = count_lines(input);

    char nums[line_count][3];
    int nums_idx = 0;
    char line[LINE_BUFFER];

    while(fgets(line, sizeof(line), input)) {
        int line_len = strlen(line);
        int last_idx = 0;
        int is_first_num_set = 0;
        char last_char;
        for (;last_idx <= line_len;) {
            int found = 0;
            if(line[last_idx] >= '0' && line[last_idx] <= '9') {
                if (is_first_num_set == 0) {
                    nums[nums_idx][0] = line[last_idx];
                    is_first_num_set = 1;
                    last_char = line[last_idx];
                }    

                last_char = line[last_idx];
                last_idx++;
                found = 1;
            }

            for (int j = 0; found != 1 && j < NUM_WORDS_LENGTH; j++) {
                if (indexof(line + last_idx, NUM_WORDS[j]) == 0) {
                    if (is_first_num_set == 0) {
                        nums[nums_idx][0] = j + 1 + '0';
                        is_first_num_set = 1;
                    }    

                    last_char = j + 1 + '0';
                    last_idx++;
                    found = 1;
                }
            }

            if (found == 0) {
                last_idx++;
            } 
        }

        nums[nums_idx][1] = last_char;
        nums[nums_idx++][2] = '\0';

        printf("\n");
    }


    int ans = 0;
    for(int i = 0; i < line_count; i++) {
        printf("%s\n", nums[i]);
        ans += atoi(nums[i]);
    }

    printf("ans: %d\n", ans);
    fclose(input);
    return 0;
}

int count_lines(FILE* file) {
    int count = 0;
    char res[LINE_BUFFER];
    while(fgets(res, sizeof(res), file)) {
        count++;
    }
    rewind(file);
    return count;
}

int indexof(const char* haystack, const char* needle) {
    char* needle_location = strstr(haystack, needle);
    if (needle_location == NULL) {
        return -1;
    }

    return needle_location - haystack; 
}
