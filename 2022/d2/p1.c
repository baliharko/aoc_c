#include <stdio.h>
#include <string.h>

#define WIN 6
#define DRAW 3
#define LOSS 0

#define LINE_BUFFER 8

int get_score(char player, char opponent);
int mod(int a, int b);

int main(void) {
    FILE* file = fopen("2022/d2/input.txt", "r");
    if (!file) {
        printf("Error opening file.");
        return 1;
    }

    char res[LINE_BUFFER];
    int ans = 0;
    while(fgets(res, sizeof(res), file)) {
        char opponent = strtok(res, " ")[0];
        char player = strtok(NULL, " ")[0];
        ans += get_score(player, opponent); 
    }

    fclose(file);
    printf("ans: %d\n", ans);
    return 0;
}

int mod(int a, int b) {
    return ((a % b) + b) % b;
}

int get_score(char player, char opponent) {
    int p = player - 'X';
    int o = opponent - 'A';

    if (o == p) {
        return DRAW + (p + 1);
    } else if (o == mod(p + 1, 3)) {
        return LOSS + (p + 1);
    } else {
        return WIN + (p + 1);
    }
}

