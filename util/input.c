#include "input.h"
#include "dynarray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        int last_idx = strlen(line) - 1;
        if(line[last_idx] == '\n') {
            line[last_idx] = '\0';
        }

        push_back(vector, line, sizeof(line));
    }

    fclose(file);
}
