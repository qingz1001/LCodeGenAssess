#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PLAYERS 10
#define MAX_CARDS 2000
#define MAX_HAND 100

typedef struct {
    char role[3];
    char hand[MAX_HAND][2];
    int handSize;
    int hp;
    bool hasWeapon;
    bool isDead;
    bool hasRevealed;
    bool isLikelyFP;
} Player;

Player players[MAX_PLAYERS];
char deck[MAX_CARDS][2];
int deckSize;
int n, m;

void initGame() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", players[i].role);
        for (int j = 0; j < 4; j++) {
            scanf("%s", players[i].hand[j]);
        }
        players[i].handSize = 4;
        players[i].hp = 4;
        players[i].hasWeapon = false;
        players[i].isDead = false;
        players[i].hasRevealed = (i == 0);  // MP is always revealed
        players[i].isLikelyFP = false;
    }
    for (int i = 0; i < m; i++) {
        scanf("%s", deck[i]);
    }
    deckSize = m;
}

void drawCards(int player, int count) {
    for (int i = 0; i < count; i++) {
        if (deckSize > 0) {
            strcpy(players[player].hand[players[player].handSize++], deck[--deckSize]);
        } else {
            strcpy(players[player].hand[players[player].handSize++], deck[deckSize]);
        }
    }
}

void useCard(int player, int cardIndex) {
    for (int i = cardIndex; i < players[player].handSize - 1; i++) {
        strcpy(players[player].hand[i], players[player].hand[i + 1]);
    }
    players[player].handSize--;
}

bool hasCard(int player, char cardType) {
    for (int i = 0; i < players[player].handSize; i++) {
        if (players[player].hand[i][0] == cardType) {
            return true;
        }
    }
    return false;
}

int findCard(int player, char cardType) {
    for (int i = 0; i < players[player].handSize; i++) {
        if (players[player].hand[i][0] == cardType) {
            return i;
        }
    }
    return -1;
}

void playTurn(int player) {
    // Draw phase
    drawCards(player, 2);

    // Play phase
    while (true) {
        // Use Peach if possible
        while (players[player].hp < 4 && hasCard(player, 'P')) {
            int cardIndex = findCard(player, 'P');
            useCard(player, cardIndex);
            players[player].hp++;
        }

        // Use equipment
        int equipIndex = findCard(player, 'Z');
        if (equipIndex != -1) {
            useCard(player, equipIndex);
            players[player].hasWeapon = true;
        }

        // Use AOE cards
        char aoeCards[] = {'N', 'W'};
        for (int i = 0; i < 2; i++) {
            int cardIndex = findCard(player, aoeCards[i]);
            if (cardIndex != -1) {
                useCard(player, cardIndex);
                for (int target = 0; target < n; target++) {
                    if (target != player && !players[target].isDead) {
                        char reqCard = (aoeCards[i] == 'N') ? 'K' : 'D';
                        if (hasCard(target, reqCard)) {
                            int defenseIndex = findCard(target, reqCard);
                            useCard(target, defenseIndex);
                        } else {
                            players[target].hp--;
                            if (players[target].hp <= 0) {
                                players[target].isDead = true;
                            }
                        }
                    }
                }
            }
        }

        // Use Kill or Duel based on role
        bool usedKill = false;
        for (int i = 1; i < n; i++) {
            int target = (player + i) % n;
            if (!players[target].isDead) {
                if (strcmp(players[player].role, "MP") == 0) {
                    if (players[target].isLikelyFP || players[target].hasRevealed) {
                        if (!usedKill && hasCard(player, 'K')) {
                            int killIndex = findCard(player, 'K');
                            useCard(player, killIndex);
                            usedKill = true;
                            if (hasCard(target, 'D')) {
                                int dodgeIndex = findCard(target, 'D');
                                useCard(target, dodgeIndex);
                            } else {
                                players[target].hp--;
                                if (players[target].hp <= 0) {
                                    players[target].isDead = true;
                                }
                            }
                        } else if (hasCard(player, 'F')) {
                            int duelIndex = findCard(player, 'F');
                            useCard(player, duelIndex);
                            while (true) {
                                if (!hasCard(target, 'K')) {
                                    players[target].hp--;
                                    if (players[target].hp <= 0) {
                                        players[target].isDead = true;
                                    }
                                    break;
                                }
                                int targetKillIndex = findCard(target, 'K');
                                useCard(target, targetKillIndex);
                                if (!hasCard(player, 'K')) {
                                    players[player].hp--;
                                    if (players[player].hp <= 0) {
                                        players[player].isDead = true;
                                    }
                                    break;
                                }
                                int playerKillIndex = findCard(player, 'K');
                                useCard(player, playerKillIndex);
                            }
                        }
                        break;
                    }
                } else if (strcmp(players[player].role, "ZP") == 0) {
                    if (players[target].hasRevealed && strcmp(players[target].role, "FP") == 0) {
                        // Similar logic for ZP attacking revealed FP
                        break;
                    }
                } else if (strcmp(players[player].role, "FP") == 0) {
                    if (strcmp(players[target].role, "MP") == 0 || 
                        (players[target].hasRevealed && strcmp(players[target].role, "ZP") == 0)) {
                        // Similar logic for FP attacking MP or revealed ZP
                        break;
                    }
                }
            }
        }

        // Break if no more actions possible
        break;
    }
}

bool isGameOver() {
    bool mpAlive = false;
    bool fpAlive = false;
    for (int i = 0; i < n; i++) {
        if (!players[i].isDead) {
            if (strcmp(players[i].role, "MP") == 0) {
                mpAlive = true;
            } else if (strcmp(players[i].role, "FP") == 0) {
                fpAlive = true;
            }
        }
    }
    return !mpAlive || !fpAlive;
}

void printResult() {
    bool mpWin = false;
    for (int i = 0; i < n; i++) {
        if (!players[i].isDead && strcmp(players[i].role, "MP") == 0) {
            mpWin = true;
            break;
        }
    }
    printf("%s\n", mpWin ? "MP" : "FP");

    for (int i = 0; i < n; i++) {
        if (players[i].isDead) {
            printf("DEAD\n");
        } else if (players[i].handSize == 0) {
            printf("\n");
        } else {
            for (int j = 0; j < players[i].handSize; j++) {
                printf("%s", players[i].hand[j]);
                if (j < players[i].handSize - 1) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
}

int main() {
    initGame();
    while (!isGameOver()) {
        for (int i = 0; i < n; i++) {
            if (!players[i].isDead) {
                playTurn(i);
                if (isGameOver()) break;
            }
        }
    }
    printResult();
    return 0;
}