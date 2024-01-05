#include "../../util/input.h"
#include "../../util/dynarray.h"

DynArray input;

int main(void) {

    const char* str = lines_as_contiguous_string("2023/d3/example.txt", 69699);
    printf("%s\n", str);

    return 0;
}
