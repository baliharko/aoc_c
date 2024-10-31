#include <stdio.h>
#include <string.h>
#include "common.h" 
#include "dynarray.h"
#include "input.h"


void tokenize(char* str, char* delimiter, char** target, int target_size);

int occurences(char* str, char c);

int main(void) {
    init_cubes(0, 0, 0); 

    DynArray input;
    lines_to_dynarray("2023/d2/input.txt", &input);

    char* last_game_index = element_at(&input, input.size - 1) + strlen("Game ");
    int games_amt = atoi(&last_game_index[0]);
    int cube_sums[games_amt];

    for(size_t i = 0; i < input.size; i++) {
        char* line = element_at(&input, i);
        char* save_line;
        strtok_r(line, ":", &save_line);

        int hands_amt = occurences(save_line, ';') + 1;
        char* hands[hands_amt];
        tokenize(save_line, ";", hands, sizeof(hands));

        for(int j = 0; j < hands_amt; ++j) {
            int cube_occurences = occurences(hands[j], ',') + 1;
            char* cubes[cube_occurences];
            tokenize(hands[j], ",", cubes, sizeof(cubes));

            for(int k = 0; k < cube_occurences; k++) {
                char* tokens[2];
                tokenize(cubes[k], " ", tokens, sizeof(tokens));

                int cube_amt = atoi(tokens[0]);
                if (get_cube_current_amt(tokens[1][0]) < cube_amt) {
                    set_cube(tokens[1][0], cube_amt);
                } 
            }
        }
        
        cube_sums[i] = get_cube_current_amt('r') * get_cube_current_amt('g') * get_cube_current_amt('b');              
        init_cubes(0, 0, 0);
    }

    int ans = 0;
    for(int i = 0; i < games_amt; i++) {
        ans += cube_sums[i]; 
    }

    printf("ans: %d\n", ans);

    return 0;
}

void tokenize(char* str, char* delimiter, char** target, int target_size) {
    char* save_ptr;
    int idx = 0;
    char* token;
    for(token = strtok_r(str, delimiter, &save_ptr); save_ptr != NULL; token = strtok_r(save_ptr, delimiter, &save_ptr)) {
        if (idx >= target_size / 8) // sizeof(char*)
            return;

        target[idx++] = token;
    }

    target[idx] = token;
}

int occurences(char* str, char c) {
    int idx = 0;
    int occurences = 0;
    int len = strlen(str);

    for(; idx < len; occurences += str[idx++] == c ? 1 : 0);
    return occurences;
}

