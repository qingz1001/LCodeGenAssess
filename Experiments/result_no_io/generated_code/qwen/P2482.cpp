#include <stdio.h>
#include <string.h>

#define MAX_PLAYERS 10
#define MAX_HAND_SIZE 8
#define MAX_DECK_SIZE 2000

typedef struct {
    char role;
    char hand[MAX_HAND_SIZE][2];
    int health;
    int max_health;
    int is_alive;
} Player;

void draw_cards(Player *player, char *deck, int *deck_index) {
    for (int i = 0; i < 2; i++) {
        if (*deck_index >= strlen(deck)) {
            strcpy(player->hand[i], deck[strlen(deck) - 1]);
        } else {
            strcpy(player->hand[i], deck[*deck_index]);
            (*deck_index)++;
        }
    }
}

void play_turn(Player *players, int num_players, int *deck, int *deck_index) {
    for (int i = 0; i < num_players; i++) {
        if (!players[i].is_alive) continue;

        // Draw cards
        draw_cards(&players[i], deck, deck_index);

        // Play cards based on rules
        // Simplified logic for demonstration purposes
        for (int j = 0; j < 2; j++) {
            if (strcmp(players[i].hand[j], "P") == 0 && players[i].health < players[i].max_health) {
                players[i].health++;
                printf("Player %d used a Peach and healed to %d\n", i + 1, players[i].health);
            } else if (strcmp(players[i].hand[j], "K") == 0) {
                printf("Player %d played a Kill card\n", i + 1);
            } else if (strcmp(players[i].hand[j], "D") == 0) {
                printf("Player %d played a Defuse card\n", i + 1);
            } else if (strcmp(players[i].hand[j], "F") == 0) {
                printf("Player %d played a Duel card\n", i + 1);
            } else if (strcmp(players[i].hand[j], "N") == 0) {
                printf("Player %d played a South Pig Invasion card\n", i + 1);
            } else if (strcmp(players[i].hand[j], "W") == 0) {
                printf("Player %d played a Thousand Arrows card\n", i + 1);
            } else if (strcmp(players[i].hand[j], "J") == 0) {
                printf("Player %d played an Unshakable card\n", i + 1);
            }
        }

        // Check if player is still alive
        if (players[i].health <= 0 && strcmp(players[i].hand[0], "") != 0) {
            players[i].is_alive = 0;
            printf("Player %d is DEAD\n", i + 1);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Player players[MAX_PLAYERS];
    char deck[MAX_DECK_SIZE];

    for (int i = 0; i < n; i++) {
        scanf(" %c %s %s %s %s", &players[i].role, players[i].hand[0], players[i].hand[1], players[i].hand[2], players[i].hand[3]);
        players[i].health = 4;
        players[i].max_health = 4;
        players[i].is_alive = 1;
    }

    scanf("%s", deck);

    int deck_index = 0;
    while (deck_index < m) {
        play_turn(players, n, deck, &deck_index);
    }

    // Determine the winner
    int mp_count = 0, fp_count = 0;
    for (int i = 0; i < n; i++) {
        if (players[i].is_alive) {
            if (players[i].role == 'M') {
                mp_count++;
            } else if (players[i].role == 'F') {
                fp_count++;
            }
        }
    }

    if (mp_count > 0 && fp_count == 0) {
        printf("MP\n");
    } else {
        printf("FP\n");
    }

    for (int i = 0; i < n; i++) {
        if (players[i].is_alive) {
            printf("%s %s %s %s\n", players[i].hand[0], players[i].hand[1], players[i].hand[2], players[i].hand[3]);
        } else {
            printf("DEAD\n");
        }
    }

    return 0;
}