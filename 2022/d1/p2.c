#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 8

int count_elves(FILE* file); 

int main() {
    FILE* file = fopen("2022/d1/input.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int elves_count = count_elves(file);
    rewind(file);

    char line[BUFFER_SIZE];
    int elf_cals[elves_count];
    int elf_cals_idx = 0;
    int sum_cals = 0;
    while(1) {
        fgets(line, sizeof(line), file);
        if(feof(file)) {
            elf_cals[elf_cals_idx] = sum_cals;
            break;
        }

        if(line[0] == '\n') {
            elf_cals[elf_cals_idx++] = sum_cals;
            sum_cals = 0;
        } else
            sum_cals += atoi(line);
    }

    for (int i = 0; i < elves_count - 1; i++) {
        for (int j = 0; j < elves_count - i - 1; j++) {
            if (elf_cals[j] > elf_cals[j + 1]) {
                int temp = elf_cals[j + 1];
                elf_cals[j + 1] = elf_cals[j];
                elf_cals[j] = temp;
            }
        }
    }

    int ans = 0;
    for (int i = elves_count - 1; i > elves_count - 4 ; i--) {
        ans += elf_cals[i];
    }

    fclose(file);
    printf("Answer: %d\n", ans);
    return 0;
}

int count_elves(FILE *file) {
    int elves = 0; 
    char res[BUFFER_SIZE];
    while (fgets(res, BUFFER_SIZE, file) != NULL) {
        if (res[0] == '\n')
            elves++;
    }

    if (strlen(res) > 1) {
        elves++;
    }

    return elves;
}
