#include <stdio.h>
#include <string.h>

#define WIN_POINTS 6
#define DRAW_POINTS 3
#define WIN 'Z'
#define DRAW 'Y'
#define LOSE 'X'

#define LINE_BUFFER 8

int get_score(char player, char opponent);
int mod(int a, int b);

int main(void) {
    FILE* file = fopen("2022/d2/example.txt", "r");
    if (!file) {
        printf("Error opening file.");
        return 1;
    }

    char res[LINE_BUFFER];
    int ans = 0;
    while(fgets(res, sizeof(res), file)) {
        char opponent = strtok(res, " ")[0];
        char required_move = strtok(NULL, " ")[0];
        ans += get_score(opponent, required_move); 
    }

    fclose(file);
    printf("ans: %d\n", ans);
    return 0;
}

int mod(int a, int b) {
    return ((a % b) + b) % b;
}

int get_score(char opponent, char required_move) {
    int o = opponent - 'A';
    switch(required_move) {
        case WIN:
            return mod(o + 1, 3) + 1 + WIN_POINTS;
            break;
        case DRAW:
            return o + 1 + DRAW_POINTS;
            break;
        case LOSE:
            return mod(o + 2, 3) + 1;
            break;
        default:
            return -1;
            break;
    }
}

