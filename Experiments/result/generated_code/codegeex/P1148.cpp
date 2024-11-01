#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARDS 16
#define MAX_PLAYERS 4

int card_scores[] = {-50, -2, -3, -4, -5, -6, -7, -8, -9, -10, -20, -30, -40};

int calculate_score(char** cards, int* card_count) {
    int score = 0;
    int has_h1_to_h13 = 1;
    int has_s12 = 0;
    int has_d11 = 0;
    int has_c10 = 0;

    for (int i = 0; i < card_count[0]; i++) {
        if (strcmp(cards[i], "H1") == 0 || strcmp(cards[i], "H2") == 0 || strcmp(cards[i], "H3") == 0 || strcmp(cards[i], "H4") == 0 ||
            strcmp(cards[i], "H5") == 0 || strcmp(cards[i], "H6") == 0 || strcmp(cards[i], "H7") == 0 || strcmp(cards[i], "H8") == 0 ||
            strcmp(cards[i], "H9") == 0 || strcmp(cards[i], "H10") == 0 || strcmp(cards[i], "H11") == 0 || strcmp(cards[i], "H12") == 0 ||
            strcmp(cards[i], "H13") == 0) {
            has_h1_to_h13 = 0;
        }
        if (strcmp(cards[i], "S12") == 0) {
            has_s12 = 1;
        }
        if (strcmp(cards[i], "D11") == 0) {
            has_d11 = 1;
        }
        if (strcmp(cards[i], "C10") == 0) {
            has_c10 = 1;
        }
    }

    if (has_h1_to_h13) {
        if (has_s12 && has_d11) {
            score += 500;
        } else {
            score += 200;
        }
    } else {
        if (has_s12) {
            score -= 100;
        }
        if (has_d11) {
            score += 100;
        }
        for (int i = 0; i < card_count[0]; i++) {
            if (strncmp(cards[i], "H", 1) == 0) {
                int card_num = atoi(cards[i] + 1);
                score += card_scores[card_num - 1];
            }
        }
    }

    if (has_c10) {
        if (card_count[0] == 1) {
            score += 50;
        } else {
            score *= 2;
        }
    }

    return score;
}

int main() {
    char input[256];
    char** cards[MAX_PLAYERS][MAX_CARDS];
    int card_count[MAX_PLAYERS] = {0};

    while (1) {
        int total_cards[MAX_PLAYERS] = {0};
        for (int i = 0; i < MAX_PLAYERS; i++) {
            if (fgets(input, sizeof(input), stdin) == NULL) {
                return 0;
            }
            if (sscanf(input, "%d", &total_cards[i]) != 1) {
                return 0;
            }
            if (total_cards[i] == 0) {
                if (i == 3) {
                    break;
                }
                continue;
            }
            cards[i] = (char**)malloc(total_cards[i] * sizeof(char*));
            for (int j = 0; j < total_cards[i]; j++) {
                cards[i][j] = (char*)malloc(4 * sizeof(char));
                if (sscanf(input, "%s", cards[i][j]) != 1) {
                    return 0;
                }
            }
            card_count[i] = total_cards[i];
        }

        int scores[MAX_PLAYERS];
        for (int i = 0; i < MAX_PLAYERS; i++) {
            scores[i] = calculate_score(cards[i], &card_count[i]);
        }

        for (int i = 0; i < MAX_PLAYERS; i++) {
            if (scores[i] > 0) {
                printf("+%d ", scores[i]);
            } else {
                printf("%d ", scores[i]);
            }
        }
        printf("\n");

        for (int i = 0; i < MAX_PLAYERS; i++) {
            for (int j = 0; j < card_count[i]; j++) {
                free(cards[i][j]);
            }
            free(cards[i]);
        }
    }

    return 0;
}