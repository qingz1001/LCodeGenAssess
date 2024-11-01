#include <stdio.h>
#include <string.h>

#define MAX_CARDS 16

int parse_card(char *card) {
    int suit, rank;
    if (card[0] == 'S') suit = 0;
    else if (card[0] == 'H') suit = 1;
    else if (card[0] == 'D') suit = 2;
    else if (card[0] == 'C') suit = 3;
    else return -1;

    rank = atoi(card + 1);
    return suit * 13 + rank - 1;
}

int calculate_score(int cards[4][MAX_CARDS], int counts[4]) {
    int scores[4] = {0};
    int all_hearts[4] = {0};
    int has_c10[4] = {0};
    int has_s12[4] = {0};
    int has_d11[4] = {0};
    int heart_count = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < counts[i]; j++) {
            int card = cards[i][j];
            if (card == 9) has_c10[i] = 1;
            if (card == 11) has_s12[i] = 1;
            if (card == 33) has_d11[i] = 1;
            if (card >= 13 && card <= 25) {
                all_hearts[i] = 1;
                heart_count++;
            }
        }
    }

    int all_hearts_in_one = 0;
    for (int i = 0; i < 4; i++) {
        if (all_hearts[i] && heart_count == 13) {
            all_hearts_in_one = 1;
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (has_c10[i] && counts[i] == 1) {
            scores[i] += 50;
        } else if (has_c10[i]) {
            scores[i] *= 2;
        }

        if (all_hearts_in_one) {
            if (all_hearts[i]) {
                scores[i] += 200;
                if (has_s12[i] && has_d11[i]) {
                    scores[i] += 300;
                }
            }
        } else {
            for (int j = 0; j < counts[i]; j++) {
                int card = cards[i][j];
                if (card == 11) scores[i] -= 100;
                else if (card == 33) scores[i] += 100;
                else if (card >= 13 && card <= 25) {
                    int heart_scores[] = {-50, -2, -3, -4, -5, -6, -7, -8, -9, -10, -20, -30, -40};
                    scores[i] += heart_scores[card - 13];
                }
            }
        }
    }

    return scores[0] + scores[1] + scores[2] + scores[3];
}

int main() {
    int cards[4][MAX_CARDS];
    int counts[4];
    char input[100];

    while (1) {
        int total_cards = 0;
        for (int i = 0; i < 4; i++) {
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%d", &counts[i]);
            total_cards += counts[i];
            for (int j = 0; j < counts[i]; j++) {
                fgets(input, sizeof(input), stdin);
                cards[i][j] = parse_card(input);
            }
        }

        if (total_cards == 0) break;

        int scores[4];
        for (int i = 0; i < 4; i++) {
            scores[i] = calculate_score(cards, counts);
        }

        for (int i = 0; i < 4; i++) {
            printf("%d", scores[i]);
            if (i < 3) printf(" ");
        }
        printf("\n");
    }

    return 0;
}