#include "dynarray.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_MAX 65536
#define TOKENS_COUNT 2
#define CARDS_PER_HAND 5

typedef struct {
    int64_t first;
    int64_t last;
} Range;

enum HandType {
    HIGH_CARD = 0,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND
};

typedef struct {
    char *cards;
    enum HandType handType;
    int bid;
} Hand;

enum HandType getHandType(const char* cards) {
    int chars[127] = { 0 };

    int len = strlen(cards);
    for (int i = 0; i < len; i++) {
        int c = cards[i];
        chars[c]++;
    }

    int occurrences = 0;
    for (int i = 0; i < 127; i++) {
        if (chars[i] > 0) occurrences++; 
    }

    int nonZeroOccurrences[occurrences];
    int idx = 0;
    for (int i = 0; i < 127; i++) {
        if (chars[i] > 0) {
            nonZeroOccurrences[idx++] = chars[i];
        }
    }

    for (int i = 0; i < occurrences - 1; i++) {
        for (int j = 0; j < occurrences - i - 1; j++) {
            if (nonZeroOccurrences[j] < nonZeroOccurrences[j + 1]) {
                int temp = nonZeroOccurrences[j + 1];
                nonZeroOccurrences[j + 1] = nonZeroOccurrences[j];
                nonZeroOccurrences[j] = temp;
            }
        }
    }

    switch(occurrences) {
        case 1:
            return FIVE_OF_A_KIND; // [5]
            break;
        case 2:
            if (nonZeroOccurrences[0] == 4) // [4, 1]
                return FOUR_OF_A_KIND;
            else
                return FULL_HOUSE; // [3, 2]
            break;
        case 3:
            if (nonZeroOccurrences[0] == 3) // [3, 1, 1]
                return THREE_OF_A_KIND;
            else
                return TWO_PAIR; // [2, 2, 1]
            break;
        case 4:
            return ONE_PAIR; // [2, 1, 1, 1]
            break;
        default:
            return HIGH_CARD; // [1, 1, 1, 1, 1]
            break;
    }
}

char **tokens(char *str) {
    char **tokens = malloc(TOKENS_COUNT * sizeof(char*));
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

void swap(Hand *a, Hand *b) {
    Hand temp = *a;
    *a = *b;
    *b = temp;
}

int idxof(const char *haystack, char c) {
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

void sortHands(DynArray *hands) {
    for (size_t i = 0; i < hands->size - 1; i++) {
        for (size_t j = 0; j < hands->size - i - 1; j++) {
            Hand *h1 = element_at(hands, j);
            Hand *h2 = element_at(hands, j + 1);
            if (h1->handType > h2->handType) {
                swap(h1, h2);          
            }
        }
    } 
    
    Range handTypeChunkIndexes[FIVE_OF_A_KIND + 1] = { {0, 0} };
    for (size_t i = 0; i < hands->size - 1; i++) {
        Hand *h1 = element_at(hands, i);
        Hand *h2 = element_at(hands, i + 1);

        if (i + 1 == hands->size - 1) {
            handTypeChunkIndexes[h2->handType].last = i + 1;
        }

        if (h2->handType > h1->handType) {
            handTypeChunkIndexes[h1->handType].last = i;            
            handTypeChunkIndexes[h2->handType].first = i + 1;
        }
    }

    const char *VALUES = "23456789TJQKA";
    for (int i = 0; i <= FIVE_OF_A_KIND; i++) {
        Range r = handTypeChunkIndexes[i];

        if (r.first == r.last) continue;

        int chunkSize = r.last - r.first + 1;
        for (int pass = 0; pass < chunkSize - 1; pass++) {
            for (int k = r.first; k < r.last - pass; k++) {
                Hand *h1 = element_at(hands, k);
                Hand *h2 = element_at(hands, k + 1);
                for (int v = 0; v < CARDS_PER_HAND; v++) {
                    int h1Rank = idxof(VALUES, h1->cards[v]);
                    int h2Rank = idxof(VALUES, h2->cards[v]);

                    if (h1Rank < h2Rank) break;

                    if (h1Rank > h2Rank) {
                        swap(h1, h2);
                        break;
                    }
                }
            }
        }
    }
}

int main(void) {
    FILE *input = fopen("2023/d7/input.txt", "r");
    if (input == NULL) {
        perror("Error opening file.");
        return 1;
    }

    DynArray hands;
    init_dynarray(&hands);

    char line[LINE_MAX];
    while (fgets(line, LINE_MAX, input)) {
        char **toks = tokens(line);
        Hand h;
        h.cards = strdup(*toks);
        h.handType = getHandType(h.cards);
        h.bid = atoi(toks[1]);
        push_back(&hands, &h, sizeof(Hand));
    }
    fclose(input);

    sortHands(&hands);

    uint64_t ans = 0;
    for (size_t i = 0; i < hands.size; i++) {
        Hand *h = element_at(&hands, i);
        ans += h->bid * (i + 1);
    }

    printf("ans: %llu\n", ans);
    return 0;
}
