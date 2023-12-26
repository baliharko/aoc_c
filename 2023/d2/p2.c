#include "common.h"
#include <stdio.h>
#include "../../util/dynarray.h"
#include "../../util/input.h"

/*
    * count games -> create array same length as games -> later put sum_cubes in gameId index
        - take gameId of last line in input

    * get min cubes [r, g, b] per game
        - CUBES['r'] * CUBES['g'] * CUBES['b']
        - init_cubes(0, 0, 0)

    * sum min cubes per game r*g*b

    * add it all up
*/

int main(void) {
    init_cubes(0, 0, 0); 

    DynArray input;
    lines_to_dynarray("2023/d2/input.txt", &input);

    char* last = element_at(&input, input.size - 1) + strlen("Game ");
    int games_amt = atoi(&last[0]);
    
    int cube_sums[games_amt];

    for(size_t i = 0; i < input.size; ++i) {
        char* element = element_at(&input, i);
        printf("read element: %s", element);
    }

    return 0;
}
