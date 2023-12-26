#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"

#define LINE_BUFFER 4096

FILE *input;

int is_game_possible() {
    return get_cube_current_amt('r') >= 0 && get_cube_current_amt('g') >= 0 && get_cube_current_amt('b') >= 0;
}

void sum_possible_games(char* line, int* accumulator) {
    char* game_id = line + 5; // instead of calling strlen on "Game " every time.
    int is_current_game_possible = true;

    char* save_line_ptr;
    char* save_hand_ptr;
    strtok_r(line, ":", &save_line_ptr);
    for(char* hand = strtok_r(save_line_ptr, ";", &save_line_ptr); hand != NULL; hand = strtok_r(save_line_ptr, ";", &save_line_ptr)) {
        for(char* color = strtok_r(hand, ",", &save_hand_ptr); color != NULL; color = strtok_r(save_hand_ptr, ",", &save_hand_ptr)) {
            char* save_cube_ptr;
            char* amt = strtok_r(color + 1, " ", &save_cube_ptr);
            char cube_color = strtok_r(save_cube_ptr, " ", &save_cube_ptr)[0];

            set_cube(cube_color, get_cube_current_amt(cube_color) - atoi(amt));
        }

        if (is_game_possible() != true) 
            is_current_game_possible = false;
        
        init_cubes(12, 13, 14);
    }

    if (is_current_game_possible == true) 
        *accumulator += atoi(game_id);
}

int main(void) {
    init_cubes(12, 13, 14);

    input = fopen("2023/d2/input.txt", "r");
    if (input == NULL) {
        printf("Error opening file.");
        return 1;
    }

    char line[LINE_BUFFER];
    int ans = 0;
    while (fgets(line, LINE_BUFFER, input)) {
        sum_possible_games(line, &ans);
    }

    printf("ans: %d\n", ans);

    fclose(input);
    return 0;
}
