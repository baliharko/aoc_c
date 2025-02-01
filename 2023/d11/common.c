#include "common.h"

void getInputDimensions(FILE *f, int *width, int *height) {
    char buffer[LINE_MAX];
    fgets(buffer, LINE_MAX, f);

    int w = 0;
    int i = 0;
    while (buffer[i] != '\n') {
        w++;
        i++;
    }
    *width = w;

    int h = 1;
    while (fgets(buffer, LINE_MAX, f)) {
        h++;  
    }
    *height = h;

    rewind(f);
}

