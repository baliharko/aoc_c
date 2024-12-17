#include <stdio.h>
#include <string.h>

#include "str.h"
#include "common.h"


int main(void) {
    FILE *input = fopen("2023/d8/input.txt", "r");
    if (input == NULL) {
        perror("Error opening file.");
        return 1;
    }

    char instructions[LINE_MAX];
    fgets(instructions, LINE_MAX, input);;
    
    Node pairs[26 * 26 * 26];
    
    char line[LINE_MAX];
    while (fgets(line, LINE_MAX, input)) {
        if (line[0] == '\n') 
            continue;

        char* sanitized = sanitize(line);
        char **toks = tokens(sanitized, " "); 
        Node n;
        n.left = toks[1];
        n.right = toks[2];
        pairs[simpleHash(toks[0])] = n;
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
