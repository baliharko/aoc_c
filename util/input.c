#include "input.h"
#include "dynarray.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER 1024

static FILE* open_file(const char* filepath, const char* mode) {
    FILE* file = fopen(filepath, mode);
    if(file == NULL) {
        printf("Error opening file.");
        exit(EXIT_FAILURE);
    }

    return file;
}

void lines_to_dynarray(const char* filepath, DynArray* dyn_array) {
    init_dynarray(dyn_array);
    FILE* file = open_file(filepath, "r"); 

    char line[LINE_BUFFER];
    while(fgets(line, LINE_BUFFER, file)) {
        int last_idx = strlen(line) - 1;
        if(line[last_idx] == '\n') {
            line[last_idx] = '\0';
        }

        push_back(dyn_array, line, sizeof(line));
    }

    fclose(file);
}

const char* lines_as_contiguous_string(const char* filepath, uint32_t max_len) {
    FILE* file = open_file(filepath, "r");
    char* target = (char*)malloc(sizeof(char*) * max_len);

    char line[LINE_BUFFER];
    while(fgets(line, LINE_BUFFER, file)) {
        strlcat(target, strtok(line, "\n"), max_len);
    }

    fclose(file);
    return target;
}
