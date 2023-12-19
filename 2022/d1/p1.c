#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8

int main() {
    FILE* file = fopen("2022/d1/input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    
    char line[BUFFER_SIZE];
    int most_cals = 0;
    int current_cals = 0;
    while (fgets(line, BUFFER_SIZE, file) != NULL) {
        if(line[0] == '\n') {
            most_cals = current_cals > most_cals ? current_cals : most_cals;
            current_cals = 0;
        } else {
            current_cals += atoi(line);
        }
    }

    printf("Most cals: %d\n", most_cals);
    return 0;
}
