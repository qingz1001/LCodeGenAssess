#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PLAYERS 10
#define MAX_CARDS 2000
#define MAX_HAND 100

typedef struct {
    char role;
    char hand[MAX_HAND][2];
    int handSize;
    int health;
    int maxHealth;
    int hasWeapon;
    int isDead;
    int isRevealed;
} Player;

Player players[MAX_PLAYERS];
char deck[MAX_CARDS][2];
int deckSize;
int numPlayers;

void initGame() {
    for (int i = 0; i < numPlayers; i++) {
        players[i].health = 4;
        players[i].maxHealth = 4;
        players[i].hasWeapon = 0;
        players[i].isDead = 0;
        players[i].isRevealed = 0;
    }
    players[0].isRevealed = 1; // 主猪身份已知
}

void drawCards(int playerIndex, int count) {
    for (int i = 0; i < count; i++) {
        if (deckSize > 0) {
            strcpy(players[playerIndex].hand[players[playerIndex].handSize], deck[--deckSize]);
            players[playerIndex].handSize++;
        } else {
            strcpy(players[playerIndex].hand[players[playerIndex].handSize], deck[0]);
            players[playerIndex].handSize++;
        }
    }
}

void useCard(int playerIndex, int cardIndex) {
    for (int i = cardIndex; i < players[playerIndex].handSize - 1; i++) {
        strcpy(players[playerIndex].hand[i], players[playerIndex].hand[i+1]);
    }
    players[playerIndex].handSize--;
}

int findCard(int playerIndex, char cardType) {
    for (int i = 0; i < players[playerIndex].handSize; i++) {
        if (players[playerIndex].hand[i][0] == cardType) {
            return i;
        }
    }
    return -1;
}

void damage(int targetIndex, int amount, int sourceIndex) {
    players[targetIndex].health -= amount;
    if (players[targetIndex].health <= 0) {
        int peachIndex = findCard(targetIndex, 'P');
        while (peachIndex != -1 && players[targetIndex].health <= 0) {
            players[targetIndex].health++;
            useCard(targetIndex, peachIndex);
            peachIndex = findCard(targetIndex, 'P');
        }
        if (players[targetIndex].health <= 0) {
            players[targetIndex].isDead = 1;
            players[targetIndex].handSize = 0;
            if (players[targetIndex].role == 'F') {
                drawCards(sourceIndex, 3);
            } else if (players[targetIndex].role == 'Z' && sourceIndex == 0) {
                players[0].handSize = 0;
                players[0].hasWeapon = 0;
            }
        }
    }
}

void playTurn(int playerIndex) {
    if (players[playerIndex].isDead) return;

    // 摸牌阶段
    drawCards(playerIndex, 2);

    // 出牌阶段
    int cardIndex;
    while ((cardIndex = findCard(playerIndex, 'P')) != -1 && players[playerIndex].health < players[playerIndex].maxHealth) {
        players[playerIndex].health++;
        useCard(playerIndex, cardIndex);
    }

    while ((cardIndex = findCard(playerIndex, 'Z')) != -1) {
        players[playerIndex].hasWeapon = 1;
        useCard(playerIndex, cardIndex);
    }

    while ((cardIndex = findCard(playerIndex, 'N')) != -1 || (cardIndex = findCard(playerIndex, 'W')) != -1) {
        char cardType = players[playerIndex].hand[cardIndex][0];
        useCard(playerIndex, cardIndex);
        for (int i = 1; i < numPlayers; i++) {
            int target = (playerIndex + i) % numPlayers;
            if (!players[target].isDead) {
                int defenseCard = findCard(target, cardType == 'N' ? 'K' : 'D');
                if (defenseCard != -1) {
                    useCard(target, defenseCard);
                } else {
                    damage(target, 1, playerIndex);
                }
            }
        }
    }

    // 攻击逻辑（简化版，不考虑复杂的身份判断）
    if (players[playerIndex].role == 'M' || players[playerIndex].role == 'Z') {
        for (int i = 1; i < numPlayers; i++) {
            int target = (playerIndex + i) % numPlayers;
            if (!players[target].isDead && players[target].role == 'F') {
                while ((cardIndex = findCard(playerIndex, 'K')) != -1) {
                    useCard(playerIndex, cardIndex);
                    int dodge = findCard(target, 'D');
                    if (dodge == -1) {
                        damage(target, 1, playerIndex);
                    } else {
                        useCard(target, dodge);
                    }
                    if (!players[playerIndex].hasWeapon) break;
                }
                break;
            }
        }
    } else if (players[playerIndex].role == 'F') {
        if (!players[0].isDead) {
            while ((cardIndex = findCard(playerIndex, 'K')) != -1) {
                useCard(playerIndex, cardIndex);
                int dodge = findCard(0, 'D');
                if (dodge == -1) {
                    damage(0, 1, playerIndex);
                } else {
                    useCard(0, dodge);
                }
                if (!players[playerIndex].hasWeapon) break;
            }
        }
    }
}

int isGameOver() {
    if (players[0].isDead) return 1;
    for (int i = 1; i < numPlayers; i++) {
        if (players[i].role == 'F' && !players[i].isDead) return 0;
    }
    return 1;
}

int main() {
    scanf("%d %d", &numPlayers, &deckSize);
    
    for (int i = 0; i < numPlayers; i++) {
        char role[3], card1[3], card2[3], card3[3], card4[3];
        scanf("%s %s %s %s %s", role, card1, card2, card3, card4);
        players[i].role = role[0];
        players[i].handSize = 4;
        strcpy(players[i].hand[0], card1);
        strcpy(players[i].hand[1], card2);
        strcpy(players[i].hand[2], card3);
        strcpy(players[i].hand[3], card4);
    }

    for (int i = 0; i < deckSize; i++) {
        scanf("%s", deck[i]);
    }

    initGame();

    while (!isGameOver()) {
        for (int i = 0; i < numPlayers; i++) {
            playTurn(i);
            if (isGameOver()) break;
        }
    }

    printf("%s\n", players[0].isDead ? "FP" : "MP");

    for (int i = 0; i < numPlayers; i++) {
        if (players[i].isDead) {
            printf("DEAD\n");
        } else if (players[i].handSize == 0) {
            printf("\n");
        } else {
            for (int j = 0; j < players[i].handSize; j++) {
                printf("%s%c", players[i].hand[j], j == players[i].handSize - 1 ? '\n' : ' ');
            }
        }
    }

    return 0;
}