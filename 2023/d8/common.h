#pragma once

#include "str.h"
#include <string.h>

#define LINE_MAX 65536

char* sanitize(char* str) {
    char* clean = strReplace(str, "= (", "");
    clean = strReplace(clean, ")", "");
    clean = strReplace(clean, ",", "");
    return clean;
}

int simpleHash(const char* str) {
    if (strlen(str) != 3) { 
        perror("str cannot be longer than 3 letters.");
        return -1;
    }

    int out = 0;
    for (int i = 0; i < 3; i++) {
        out = out * 26 + (str[i] - 'A');
    }

    return out;
}

typedef struct {
    char* left;
    char* right;
} Node;
