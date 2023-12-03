#include <stdio.h>
#include <string.h>

#define ROCK 'A'
#define PAPER 'B'
#define SZISSORS 'C'
#define WIN 6
#define DRAW 3
#define LOSS 0
#define OFFSET 23

#define LINE_BUFFER 8

int get_score(char player, char opponent);

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
        ans += get_score(opponent, player); 
    }

    fclose(file);
    printf("ans: %d\n", ans);
    return 0;
}

int get_score(char opponent, char player) {
    typedef struct {
        int shape;
        int beats;
    } Shape;

    Shape shapes[3] = {
        { ROCK, SZISSORS },
        { PAPER, ROCK },
        { SZISSORS, PAPER },
    };

    int player_translated = player - OFFSET;
    if (player_translated == opponent) {
        printf("DRAW\n");
        return DRAW + player_translated - 'A' + 1;
    } else if (shapes[player_translated - 'A'].beats == opponent) {
        printf("WIN\n");
        return WIN + player_translated - 'A' + 1 ;
    } else {
        printf("LOSS\n");
        return LOSS + player_translated - 'A' + 1;
    }}

