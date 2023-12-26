#include "input.h"
#include "dynarray.h"
#include <stdio.h>
#include <stdlib.h>

#define LINE_BUFFER 1024

void lines_to_dynarray(const char* filepath, DynArray* vector) {
    init_dynarray(vector);
    FILE* file = fopen(filepath, "r");
    if(file == NULL) {
        printf("Error opening file.");
        exit(EXIT_FAILURE);
    }

    char line[LINE_BUFFER];
    while(fgets(line, LINE_BUFFER, file)) {
        push_back(vector, line, sizeof(line));
    }

    fclose(file);
}
