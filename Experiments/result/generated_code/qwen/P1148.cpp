#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARDS 16
#define NUM_PLAYERS 4

typedef struct {
    int count;
    char cards[MAX_CARDS][3];
} Player;

int getScore(const char *card) {
    if (strcmp(card, "S12") == 0) return -100;
    if (strcmp(card, "D11") == 0) return 100;
    if (strcmp(card, "C10") == 0) return 50;
    for (int i = 1; i <= 13; i++) {
        char expected[3];
        sprintf(expected, "H%d", i);
        if (strcmp(card, expected) == 0) return -50 + (i - 1) * 2;
    }
    return 0;
}

void calculateScores(Player players[NUM_PLAYERS], int scores[NUM_PLAYERS]) {
    memset(scores, 0, sizeof(scores));
    int heartsInOneFamily = 1;
    int hasAllCards = 0;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (players[i].count == 0) continue;
        if (players[i].count == 16) {
            scores[i] = 1000;
            hasAllCards = 1;
        } else {
            int hasSpecialCards = 0;
            int heartValueSum = 0;
            for (int j = 0; j < players[i].count; j++) {
                int score = getScore(players[i].cards[j]);
                if (score == 50 || score == 100) {
                    hasSpecialCards = 1;
                } else if (score < 0) {
                    heartValueSum += score;
                }
            }
            if (!hasSpecialCards) {
                scores[i] = 2 * heartValueSum;
            } else if (heartValueSum != 0) {
                scores[i] = heartValueSum;
            }

            if (heartsInOneFamily && heartValueSum == 0) {
                scores[i] += 500;
            }
        }

        if (heartValueSum != 0) {
            heartsInOneFamily = 0;
        }
    }

    if (hasAllCards) {
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (scores[i] != 1000) {
                scores[i] = 0;
            }
        }
    }
}

int main() {
    Player players[NUM_PLAYERS];
    int scores[NUM_PLAYERS];

    while (1) {
        for (int i = 0; i < NUM_PLAYERS; i++) {
            scanf("%d", &players[i].count);
            if (players[i].count == 0) break;
            for (int j = 0; j < players[i].count; j++) {
                scanf("%s", players[i].cards[j]);
            }
        }

        if (players[0].count == 0) break;

        calculateScores(players, scores);

        for (int i = 0; i < NUM_PLAYERS; i++) {
            printf("%d ", scores[i]);
        }
        printf("\n");
    }

    return 0;
}