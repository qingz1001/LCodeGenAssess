#include <stdio.h>
#include <string.h>

#define MAX_CARDS 16

int calculate_score(char cards[][3], int num_cards) {
    int score = 0;
    int has_hearts[14] = {0};
    int has_s12 = 0, has_d11 = 0, has_c10 = 0;
    int all_hearts = 1;

    for (int i = 0; i < num_cards; i++) {
        if (cards[i][0] == 'H') {
            int value = cards[i][1] - '0';
            if (cards[i][2] != '\0') value = value * 10 + (cards[i][2] - '0');
            has_hearts[value] = 1;
        } else if (strcmp(cards[i], "S12") == 0) {
            has_s12 = 1;
        } else if (strcmp(cards[i], "D11") == 0) {
            has_d11 = 1;
        } else if (strcmp(cards[i], "C10") == 0) {
            has_c10 = 1;
        }
    }

    for (int i = 1; i <= 13; i++) {
        if (!has_hearts[i]) {
            all_hearts = 0;
            break;
        }
    }

    if (all_hearts) {
        score += 200 * 13;
        if (has_s12 && has_d11) score += 500;
    } else {
        int heart_scores[] = {0, -50, -2, -3, -4, -5, -6, -7, -8, -9, -10, -20, -30, -40};
        for (int i = 1; i <= 13; i++) {
            if (has_hearts[i]) score += heart_scores[i];
        }
        if (has_s12) score -= 100;
        if (has_d11) score += 100;
    }

    if (has_c10) {
        if (num_cards == 1) score = 50;
        else score *= 2;
    }

    if (num_cards == MAX_CARDS) score = 1000;

    return score;
}

int main() {
    int num_cards;
    char cards[MAX_CARDS][3];
    int scores[4];

    while (1) {
        int total_cards = 0;
        for (int player = 0; player < 4; player++) {
            scanf("%d", &num_cards);
            total_cards += num_cards;
            for (int i = 0; i < num_cards; i++) {
                scanf("%s", cards[i]);
            }
            scores[player] = calculate_score(cards, num_cards);
        }

        if (total_cards == 0) break;

        if (total_cards == MAX_CARDS) {
            for (int i = 0; i < 4; i++) {
                if (scores[i] == 1000) {
                    printf("+1000 ");
                } else {
                    printf("0 ");
                }
            }
        } else {
            for (int i = 0; i < 4; i++) {
                if (scores[i] > 0) printf("+");
                printf("%d ", scores[i]);
            }
        }
        printf("\n");
    }

    return 0;
}