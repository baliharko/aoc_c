#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 65536

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
} Node;

int64_t mod(int64_t a, int64_t b) {
    int res = a % b;
    if ((res > 0 && b < 0) || (res < 0 && b > 0)) {
        res += b;
    }
    return res;
}

uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t tmp = a;
        a = b;
        b = mod(tmp, b);
    } 

    return a;
}

uint64_t lcm(uint64_t a, uint64_t b) {
    return a * b / gcd(a, b);
}

bool allTrue(bool arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (!arr[i]) { 
            return false;
        }
    }

    return true;
}

typedef struct {
    char* current;
    uint32_t cycles;
} Ghost;

int main(void) {
    FILE *input = fopen("2023/d8/input.txt", "r");
    if (input == NULL) {
        perror("Error opening file.");
        return 1;
    }

    char instructions[LINE_MAX];
    fgets(instructions, LINE_MAX, input);;
    
    Node nodes[26 * 26 * 26];
    char* startingNodes[700] = { NULL };
    int startingNodesIdx = 0;
    
    char line[LINE_MAX];
    while (fgets(line, LINE_MAX, input)) {
        if (line[0] == '\n') 
            continue;

        char* sanitized = sanitize(line);
        char **toks = tokens(sanitized, " "); 
        Node p;
        p.left = toks[1];
        p.right = toks[2];
        nodes[simpleHash(toks[0])] = p;

        if (toks[0][2] == 'A') {
            startingNodes[startingNodesIdx++] = toks[0];
        }
    }

    fclose(input);

    int instructionsLen = strlen(instructions) - 1;
    Ghost ghosts[startingNodesIdx];
    for (int i = 0; i < startingNodesIdx; i++) {
        ghosts[i].cycles = 0;
        ghosts[i].current = startingNodes[i];
    }

    bool arrived[startingNodesIdx];
    for (int i = 0; i < startingNodesIdx; i++) {
        arrived[i] = false;
    }

    int currCycle = 0;
    while (!allTrue(arrived, startingNodesIdx)) {
        for (int i = 0; i < instructionsLen; i++) {
            for (int ghost = 0; ghost < startingNodesIdx; ghost++) {
                if (arrived[ghost]) continue;

                Ghost *g = &ghosts[ghost];
                int hash = simpleHash(g->current);
                Node n = nodes[hash];
                g->current = instructions[i] == 'L' ? n.left : n.right;
            }
        } 
        currCycle++;
        
        for (int ghost = 0; ghost < startingNodesIdx; ghost++) {
            if (arrived[ghost]) continue;

            Ghost *g = &ghosts[ghost];
            if (g->current[2] == 'Z') {
                g->cycles = currCycle;
                arrived[ghost] = true;
            }
        }
    }

    uint64_t minSharedCycles = 1;
    for (int i = 0; i < startingNodesIdx; i++) {
        minSharedCycles = lcm(minSharedCycles, ghosts[i].cycles);
    }

    uint64_t ans = minSharedCycles * instructionsLen;
    printf("ans: %llu\n", ans);

    return 0;
}
