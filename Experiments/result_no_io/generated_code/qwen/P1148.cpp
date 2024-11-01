#include <stdio.h>
#include <string.h>

#define MAX_CARDS 16
#define MAX_PLAYERS 4
#define MAX_CARD_LEN 5

typedef struct {
    char card[MAX_CARD_LEN];
} Card;

int getCardValue(Card card) {
    if (strcmp(card.card, "S12") == 0) return -100;
    if (strcmp(card.card, "D11") == 0) return 100;
    for (int i = 1; i <= 13; i++) {
        if (card.card[0] == 'H' && card.card[1] == '0' + i) {
            return -50 * (i - 1);
        }
    }
    return 0;
}

int main() {
    Card players[MAX_PLAYERS][MAX_CARDS];
    int scores[MAX_PLAYERS] = {0};
    int cardCount[MAX_PLAYERS] = {0};

    while (1) {
        for (int i = 0; i < MAX_PLAYERS; i++) {
            scanf("%d", &cardCount[i]);
            if (cardCount[i] == 0) {
                if (scores[0] != 0 || scores[1] != 0 || scores[2] != 0 || scores[3] != 0) {
                    printf("%d %d %d %d\n", scores[0], scores[1], scores[2], scores[3]);
                } else {
                    return 0;
                }
                memset(scores, 0, sizeof(scores));
                memset(cardCount, 0, sizeof(cardCount));
                break;
            }
            for (int j = 0; j < cardCount[i]; j++) {
                scanf("%s", players[i][j].card);
            }
        }

        // Check for player with all 16 cards
        int allCardsPlayer = -1;
        for (int i = 0; i < MAX_PLAYERS; i++) {
            int hasAllCards = 1;
            for (int j = 0; j < cardCount[i]; j++) {
                if (strcmp(players[i][j].card, "S12") != 0 &&
                    strcmp(players[i][j].card, "D11") != 0 &&
                    !((players[i][j].card[0] == 'H' && players[i][j].card[1] >= '1' && players[i][j].card[1] <= '3') ||
                      (players[i][j].card[0] == 'H' && players[i][j].card[1] == '0' && players[i][j].card[2] >= '4' && players[i][j].card[2] <= '9')) &&
                    strcmp(players[i][j].card, "C10") != 0) {
                    hasAllCards = 0;
                    break;
                }
            }
            if (hasAllCards) {
                allCardsPlayer = i;
                break;
            }
        }

        if (allCardsPlayer != -1) {
            scores[allCardsPlayer] += 1000;
            continue;
        }

        // Calculate scores for each player
        for (int i = 0; i < MAX_PLAYERS; i++) {
            int hasDouble = 0;
            int hasRedHearts = 0;
            int redHeartSum = 0;
            int hasPig = 0;
            int hasSheep = 0;
            int hasDoubleTen = 0;

            for (int j = 0; j < cardCount[i]; j++) {
                int value = getCardValue(players[i][j]);
                if (value != 0) {
                    scores[i] += value;
                }
                if (strcmp(players[i][j].card, "C10") == 0) {
                    hasDoubleTen = 1;
                }
                if (strcmp(players[i][j].card, "S12") == 0) {
                    hasPig = 1;
                }
                if (strcmp(players[i][j].card, "D11") == 0) {
                    hasSheep = 1;
                }
                if ((players[i][j].card[0] == 'H' && players[i][j].card[1] >= '1' && players[i][j].card[1] <= '3') ||
                    (players[i][j].card[0] == 'H' && players[i][j].card[1] == '0' && players[i][j].card[2] >= '4' && players[i][j].card[2] <= '9')) {
                    hasRedHearts = 1;
                    redHeartSum += value;
                }
            }

            if (hasDoubleTen && cardCount[i] == 1) {
                scores[i] += 50;
            } else if (hasDoubleTen) {
                scores[i] *= 2;
            }

            if (hasRedHearts) {
                if (cardCount[i] > 1) {
                    scores[i] -= redHeartSum;
                } else {
                    scores[i] -= 200;
                }
            } else {
                scores[i] += 200;
                if (hasPig && hasSheep) {
                    scores[i] += 500;
                }
            }
        }

        printf("%d %d %d %d\n", scores[0], scores[1], scores[2], scores[3]);
    }

    return 0;
}