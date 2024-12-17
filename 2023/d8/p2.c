#include "math.h"
#include "str.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "common.h"


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
