#include <stdio.h>
#include <string.h>

#define MAX_PLAYERS 10
#define MAX_HAND_SIZE 4
#define MAX_DECK_SIZE 2000

typedef enum {
    MP, ZP, FP
} Role;

typedef struct {
    Role role;
    char hand[MAX_HAND_SIZE][2];
    int life;
    int max_life;
    int is_dead;
    int has_zhuo_gun;
    int class_fp;
} Player;

typedef struct {
    char card[2];
} Card;

void initialize_players(Player players[], int n) {
    for (int i = 0; i < n; i++) {
        players[i].role = MP; // Default to MP
        players[i].life = 4;
        players[i].max_life = 4;
        players[i].is_dead = 0;
        players[i].has_zhuo_gun = 0;
        players[i].class_fp = 0;
        for (int j = 0; j < MAX_HAND_SIZE; j++) {
            strcpy(players[i].hand[j], "");
        }
    }
}

void initialize_deck(Card deck[], int m) {
    for (int i = 0; i < m; i++) {
        scanf("%s", deck[i].card);
    }
}

void draw_cards(Player *player, Card deck[], int *deck_index) {
    if (*deck_index >= 0) {
        strcat(player->hand[player->life <= player->max_life ? 0 : player->life - 1], deck[*deck_index].card);
        (*deck_index)++;
    } else {
        printf("Deck is empty.\n");
    }
}

void play_round(Player players[], int n, Card deck[], int *deck_index) {
    for (int i = 0; i < n; i++) {
        if (players[i].is_dead) continue;

        // Draw cards
        draw_cards(&players[i], deck, deck_index);

        // Play phase
        for (int j = 0; j < MAX_HAND_SIZE; j++) {
            if (strlen(players[i].hand[j]) == 0) break;

            char card = players[i].hand[j][0];
            switch (card) {
                case 'P':
                    if (players[i].life < players[i].max_life) {
                        players[i].life++;
                    }
                    break;
                case 'K':
                    if (!players[i].is_dead) {
                        int target = (i + 1) % n;
                        while (target != i && strlen(players[target].hand[0]) == 0) {
                            target = (target + 1) % n;
                        }
                        if (target != i) {
                            players[target].life--;
                            if (players[target].life <= 0) {
                                players[target].is_dead = 1;
                                if (players[target].role == FP) {
                                    draw_cards(&players[(target + 1) % n], deck, deck_index);
                                }
                            }
                        }
                    }
                    break;
                case 'D':
                    if (!players[i].is_dead) {
                        int attacker = (i - 1 + n) % n;
                        while (attacker != i && strlen(players[attacker].hand[0]) == 0) {
                            attacker = (attacker - 1 + n) % n;
                        }
                        if (attacker != i) {
                            players[attacker].life--;
                            if (players[attacker].life <= 0) {
                                players[attacker].is_dead = 1;
                                if (players[attacker].role == FP) {
                                    draw_cards(&players[(attacker + 1) % n], deck, deck_index);
                                }
                            }
                        }
                    }
                    break;
                case 'F':
                    if (!players[i].is_dead) {
                        int target = (i + 1) % n;
                        while (target != i && strlen(players[target].hand[0]) == 0) {
                            target = (target + 1) % n;
                        }
                        if (target != i) {
                            int attacker = (i - 1 + n) % n;
                            while (attacker != i && strlen(players[attacker].hand[0]) == 0) {
                                attacker = (attacker - 1 + n) % n;
                            }
                            if (attacker != i) {
                                while (1) {
                                    if (strlen(players[attacker].hand[0]) > 0 && players[attacker].hand[0][0] == 'K') {
                                        players[attacker].hand[0][0] = '\0';
                                    }
                                    if (strlen(players[target].hand[0]) > 0 && players[target].hand[0][0] == 'K') {
                                        players[target].hand[0][0] = '\0';
                                    }
                                    if (strlen(players[attacker].hand[0]) == 0 || strlen(players[target].hand[0]) == 0) {
                                        break;
                                    }
                                    attacker = (attacker + 1) % n;
                                    while (attacker != i && strlen(players[attacker].hand[0]) == 0) {
                                        attacker = (attacker + 1) % n;
                                    }
                                    target = (target - 1 + n) % n;
                                    while (target != i && strlen(players[target].hand[0]) == 0) {
                                        target = (target - 1 + n) % n;
                                    }
                                }
                                if (strlen(players[attacker].hand[0]) == 0) {
                                    players[target].life--;
                                    if (players[target].life <= 0) {
                                        players[target].is_dead = 1;
                                        if (players[target].role == FP) {
                                            draw_cards(&players[(target + 1) % n], deck, deck_index);
                                        }
                                    }
                                } else {
                                    players[attacker].life--;
                                    if (players[attacker].life <= 0) {
                                        players[attacker].is_dead = 1;
                                        if (players[attacker].role == FP) {
                                            draw_cards(&players[(attacker + 1) % n], deck, deck_index);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 'N':
                    if (!players[i].is_dead) {
                        int start = (i + 1) % n;
                        int current = start;
                        while (current != i) {
                            if (strlen(players[current].hand[0]) > 0 && players[current].hand[0][0] == 'K') {
                                players[current].hand[0][0] = '\0';
                            }
                            current = (current + 1) % n;
                        }
                        players[start].life--;
                        if (players[start].life <= 0) {
                            players[start].is_dead = 1;
                            if (players[start].role == FP) {
                                draw_cards(&players[(start + 1) % n], deck, deck_index);
                            }
                        }
                    }
                    break;
                case 'W':
                    if (!players[i].is_dead) {
                        int start = (i + 1) % n;
                        int current = start;
                        while (current != i) {
                            if (strlen(players[current].hand[0]) > 0 && players[current].hand[0][0] == 'D') {
                                players[current].hand[0][0] = '\0';
                            }
                            current = (current + 1) % n;
                        }
                        players[start].life--;
                        if (players[start].life <= 0) {
                            players[start].is_dead = 1;
                            if (players[start].role == FP) {
                                draw_cards(&players[(start + 1) % n], deck, deck_index);
                            }
                        }
                    }
                    break;
                case 'J':
                    if (!players[i].is_dead) {
                        // Handle J card logic here
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Player players[MAX_PLAYERS];
    Card deck[MAX_DECK_SIZE];

    initialize_players(players, n);
    initialize_deck(deck, m);

    int deck_index = 0;
    play_round(players, n, deck, &deck_index);

    // Determine the result
    int mp_alive = 0;
    int fp_alive = 0;
    for (int i = 0; i < n; i++) {
        if (players[i].role == MP && !players[i].is_dead) {
            mp_alive = 1;
        }
        if (players[i].role == FP && !players[i].is_dead) {
            fp_alive = 1;
        }
    }

    if (mp_alive && !fp_alive) {
        printf("MP\n");
    } else {
        printf("FP\n");
    }

    for (int i = 0; i < n; i++) {
        if (players[i].is_dead) {
            printf("DEAD\n");
        } else {
            for (int j = 0; j < MAX_HAND_SIZE; j++) {
                if (strlen(players[i].hand[j]) > 0) {
                    printf("%s ", players[i].hand[j]);
                }
            }
            printf("\n");
        }
    }

    return 0;
}