#include "common.h"

int CUBES[26] = { [0 ... 25] = 0 };

void set_cube(char color, int amount) {
    int idx = color - 'a';
    CUBES[idx] = amount;
}

int get_cube_current_amt(char color) {
    return CUBES[color - 'a'];
}

void init_cubes(int r, int g, int b) {
    set_cube('r', r);
    set_cube('g', g);
    set_cube('b', b);
}
