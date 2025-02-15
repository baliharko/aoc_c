#include <stdio.h>
#include <stdlib.h>
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

char **tokens(char *str, const char* delimiter) {
    int count = 0;
    size_t len = strlen(str);
    size_t subLen = strlen(delimiter);
    for (size_t i = 0; i <= len - subLen; i++) {
        if (strncmp(&str[i], delimiter, subLen) == 0 || str[i] == '\n') {
            count++;
        } 
    }
    count++;

    if (count == 0) {
        printf("No tokens found. Returning NULL\n");
        return NULL;
    }

    char **tokens = malloc((count + 1) * sizeof(char*));
    if (!tokens) {
        perror("malloc");
        return NULL;
    }

    char *token = strtok(str, delimiter);
    int i = 0;
    while (token != NULL) {
        int tokLen = strlen(token);
        if (tokLen > 0 && token[tokLen - 1] == '\n') {
            token[tokLen - 1] = '\0';
        }
        tokens[i++] = token;
        token = strtok(NULL, delimiter);
    }
    tokens[i] = NULL;

    return tokens;
}

int countTokens(const char *line) {
    int count = 0;
    for (const char *p = line; *p != '\0'; ++p) {
        if (*p == ' ') count++;
    }

    return count + 1;
}

char* strReplace(char *str, const char *search, const char *replace) {
    int originalLen = strlen(str);
    int searchLen = strlen(search);
    int replaceLen = strlen(replace);
    char *out = malloc((originalLen + 1) * 2);     
    
    int i, j, k;
    for (i = 0, j = 0; i <= originalLen; i++) {
        if (strncmp(&str[i], search, searchLen) == 0) {
            for (k = 0; k < replaceLen; k++) {
                out[j++] = replace[k];
            }
            i += searchLen - 1;
        } else {
            out[j++] = str[i];
        }
    }

    out[j] = '\0';
    return out;
}

int indexof_c(const char *haystack, char c) {
    int idx = -1;
    size_t len = strlen(haystack);
    for (size_t i = 0; i < len; i++) {
        if (haystack[i] == c) {
            idx = i;
            break;
        }
    }
    return idx;
}

