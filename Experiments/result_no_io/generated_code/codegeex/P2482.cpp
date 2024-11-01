#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PLAYERS 10
#define MAX_CARDS 2000

int n, m;
char players[MAX_PLAYERS][5][10];
char deck[MAX_CARDS][10];
int hand[MAX_PLAYERS][MAX_CARDS];
int num_cards[MAX_PLAYERS];
int health[MAX_PLAYERS];
int identity[MAX_PLAYERS];
int weapon[MAX_PLAYERS];
int num_alive = MAX_PLAYERS;
int current_player = 0;

int is_alive(int player) {
    return health[player] > 0;
}

void draw_cards(int player, int num) {
    for (int i = 0; i < num; i++) {
        if (m > 0) {
            strcpy(hand[player][num_cards[player]++], deck[--m]);
        } else {
            strcpy(hand[player][num_cards[player]++], deck[m]);
        }
    }
}

void play_card(int player, int index) {
    if (strcmp(hand[player][index], "P") == 0 && health[player] < 4) {
        health[player]++;
    } else if (strcmp(hand[player][index], "K") == 0) {
        // Attack logic
    } else if (strcmp(hand[player][index], "D") == 0) {
        // Defense logic
    } else if (strcmp(hand[player][index], "F") == 0) {
        // Duel logic
    } else if (strcmp(hand[player][index], "N") == 0) {
        // South Pig Invasion logic
    } else if (strcmp(hand[player][index], "W") == 0) {
        // Hundred Arrows logic
    } else if (strcmp(hand[player][index], "J") == 0) {
        // Unbreakable logic
    } else if (strcmp(hand[player][index], "Z") == 0) {
        // Pig's Crossbow logic
    }
    for (int i = index; i < num_cards[player] - 1; i++) {
        strcpy(hand[player][i], hand[player][i + 1]);
    }
    num_cards[player]--;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s %s %s %s %s", players[i][0], players[i][1], players[i][2], players[i][3], players[i][4]);
        if (strcmp(players[i][0], "MP") == 0) {
            identity[i] = 1;
            health[i] = 4;
        } else if (strcmp(players[i][0], "ZP") == 0) {
            identity[i] = 2;
            health[i] = 4;
        } else if (strcmp(players[i][0], "FP") == 0) {
            identity[i] = 3;
            health[i] = 4;
        }
        for (int j = 0; j < 4; j++) {
            strcpy(hand[i][j], players[i][j + 1]);
            num_cards[i]++;
        }
    }
    for (int i = 0; i < m; i++) {
        scanf("%s", deck[i]);
    }

    while (num_alive > 1) {
        if (is_alive(current_player)) {
            draw_cards(current_player, 2);
            // Play cards logic
        }
        current_player = (current_player + 1) % n;
    }

    if (identity[current_player] == 1) {
        printf("MP\n");
    } else {
        printf("FP\n");
    }
    if (is_alive(current_player)) {
        printf("DEAD\n");
    } else {
        for (int i = 0; i < num_cards[current_player]; i++) {
            printf("%s ", hand[current_player][i]);
        }
        printf("\n");
    }
    return 0;
}