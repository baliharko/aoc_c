#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 65536
#define TOKENS_COUNT 4

char **tokens(char *str, const char* delimiter) {
    int count = 0;
    size_t len = strlen(str);
    size_t subLen = strlen(delimiter);
    for (size_t i = 0; i <= len - subLen; i++) {
        if (strncmp(&str[i], delimiter, subLen) == 0 || str[i] == '\n') {
            count++;
        } 
    }

    char **tokens = malloc(count * sizeof(char*));
    char *token = strtok(str, " ");
    int i = 0;
    do {
        int len = strlen(token);
        if (token[len - 1] == '\n') {
            token[len - 1] = '\0';
        }

        tokens[i++] = token;
        token = strtok(NULL, " ");
    } while (token != NULL);

    return tokens;
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
} Pair;

int main(void) {
    FILE *input = fopen("2023/d8/input.txt", "r");
    if (input == NULL) {
        perror("Error opening file.");
        return 1;
    }

    char instructions[LINE_MAX];
    fgets(instructions, LINE_MAX, input);;
    
    Pair pairs[26 * 26 * 26];
    
    char line[LINE_MAX];
    while (fgets(line, LINE_MAX, input)) {
        if (line[0] == '\n') 
            continue;

        char* sanitized = sanitize(line);
        char **toks = tokens(sanitized, " "); 
        Pair p;
        p.left = toks[1];
        p.right = toks[2];
        pairs[simpleHash(toks[0])] = p;
    }

    fclose(input);

    int len = strlen(instructions);
    char *current = "AAA";
    int steps = 0;
    for (int i = 0; i < len; i++) {
        if (i == len - 1)
            i = 0;

        if (strncmp(current, "ZZZ", 3) == 0) 
            break; 


        int hash = simpleHash(current);
        current = instructions[i] == 'L' ? pairs[hash].left : pairs[hash].right;
        steps++;
    }

    printf("steps: %d\n", steps);
    return 0;
}
