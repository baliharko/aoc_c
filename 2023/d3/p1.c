#include "../../util/input.h"
#include "../../util/dynarray.h"
#include <stdio.h>

DynArray input;

int main(void) {
    lines_to_dynarray("2023/d3/example.txt", &input); 

    for(size_t i = 0; i < input.size; i++) {
        printf("%s\n", (char*)element_at(&input, i));
    }

    return 0;
}
