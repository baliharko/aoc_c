#include <stdio.h>
#include <string.h>
#include "str.h"

#define LINE_BUFFER 65535

int count_lines(FILE* file) {
    int count = 0;
    char res[LINE_BUFFER];
    while(fgets(res, sizeof(res), file)) {
        count++;
    }
    rewind(file);
    return count;
}

int indexof(const char* haystack, const char* needle) {
    char* needle_location = strstr(haystack, needle);
    if (needle_location == NULL) {
        return -1;
    }

    return needle_location - haystack; 
}

int is_digit(const char c) {
    return c >= '0' && c <= '9';
}
