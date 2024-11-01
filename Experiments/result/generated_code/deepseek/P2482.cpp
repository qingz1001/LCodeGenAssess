#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 10
#define MAX_CARDS 2000

typedef struct {
    char role;
    int health;
    int max_health;
    char hand[MAX_CARDS];
    int hand_size;
    int is_dead;
    int has_crossbow;
} Player;

Player players[MAX_PLAYERS];
char deck[MAX_CARDS];
int deck_size;
int n, m;

void init_game() {
    for (int i = 0; i < n; i++) {
        players[i].health = 4;
        players[i].max_health = 4;
        players[i].is_dead = 0;
        players[i].has_crossbow = 0;
    }
}

void draw_cards(int player_id, int num_cards) {
    for (int i = 0; i < num_cards; i++) {
        if (deck_size > 0) {
            players[player_id].hand[players[player_id].hand_size++] = deck[--deck_size];
        }
    }
}

void use_card(int player_id, char card) {
    for (int i = 0; i < players[player_id].hand_size; i++) {
        if (players[player_id].hand[i] == card) {
            memmove(&players[player_id].hand[i], &players[player_id].hand[i + 1], (players[player_id].hand_size - i - 1) * sizeof(char));
            players[player_id].hand_size--;
            break;
        }
    }
}

void attack(int attacker, int target) {
    for (int i = 0; i < players[target].hand_size; i++) {
        if (players[target].hand[i] == 'D') {
            use_card(target, 'D');
            return;
        }
    }
    players[target].health--;
    if (players[target].health <= 0) {
        players[target].is_dead = 1;
        if (players[target].role == 'FP') {
            draw_cards(attacker, 3);
        } else if (players[target].role == 'ZP' && attacker == 0) {
            players[0].hand_size = 0;
            players[0].has_crossbow = 0;
        }
    }
}

void play_game() {
    int turn = 0;
    while (1) {
        if (players[0].is_dead) {
            printf("FP\n");
            for (int i = 0; i < n; i++) {
                if (players[i].is_dead) {
                    printf("DEAD\n");
                } else {
                    for (int j = 0; j < players[i].hand_size; j++) {
                        printf("%c ", players[i].hand[j]);
                    }
                    printf("\n");
                }
            }
            return;
        }
        if (players[turn].is_dead) {
            turn = (turn + 1) % n;
            continue;
        }
        draw_cards(turn, 2);
        for (int i = 0; i < players[turn].hand_size; i++) {
            if (players[turn].hand[i] == 'P' && players[turn].health < players[turn].max_health) {
                players[turn].health++;
                use_card(turn, 'P');
            } else if (players[turn].hand[i] == 'K') {
                int target = (turn + 1) % n;
                while (target != turn && (players[target].is_dead || players[target].role == 'ZP')) {
                    target = (target + 1) % n;
                }
                if (target != turn) {
                    attack(turn, target);
                    use_card(turn, 'K');
                }
            } else if (players[turn].hand[i] == 'F') {
                int target = (turn + 1) % n;
                while (target != turn && (players[target].is_dead || players[target].role == 'ZP')) {
                    target = (target + 1) % n;
                }
                if (target != turn) {
                    while (1) {
                        if (players[target].hand_size > 0 && players[target].hand[0] == 'K') {
                            use_card(target, 'K');
                        } else {
                            players[target].health--;
                            if (players[target].health <= 0) {
                                players[target].is_dead = 1;
                                if (players[target].role == 'FP') {
                                    draw_cards(turn, 3);
                                } else if (players[target].role == 'ZP' && turn == 0) {
                                    players[0].hand_size = 0;
                                    players[0].has_crossbow = 0;
                                }
                            }
                            break;
                        }
                        if (players[turn].hand_size > 0 && players[turn].hand[0] == 'K') {
                            use_card(turn, 'K');
                        } else {
                            players[turn].health--;
                            if (players[turn].health <= 0) {
                                players[turn].is_dead = 1;
                                if (players[turn].role == 'FP') {
                                    draw_cards(target, 3);
                                } else if (players[turn].role == 'ZP' && target == 0) {
                                    players[0].hand_size = 0;
                                    players[0].has_crossbow = 0;
                                }
                            }
                            break;
                        }
                    }
                    use_card(turn, 'F');
                }
            } else if (players[turn].hand[i] == 'N') {
                for (int j = 1; j < n; j++) {
                    int target = (turn + j) % n;
                    if (!players[target].is_dead) {
                        for (int k = 0; k < players[target].hand_size; k++) {
                            if (players[target].hand[k] == 'K') {
                                use_card(target, 'K');
                                break;
                            }
                        }
                        if (players[target].health > 0) {
                            players[target].health--;
                            if (players[target].health <= 0) {
                                players[target].is_dead = 1;
                                if (players[target].role == 'FP') {
                                    draw_cards(turn, 3);
                                } else if (players[target].role == 'ZP' && turn == 0) {
                                    players[0].hand_size = 0;
                                    players[0].has_crossbow = 0;
                                }
                            }
                        }
                    }
                }
                use_card(turn, 'N');
            } else if (players[turn].hand[i] == 'W') {
                for (int j = 1; j < n; j++) {
                    int target = (turn + j) % n;
                    if (!players[target].is_dead) {
                        for (int k = 0; k < players[target].hand_size; k++) {
                            if (players[target].hand[k] == 'D') {
                                use_card(target, 'D');
                                break;
                            }
                        }
                        if (players[target].health > 0) {
                            players[target].health--;
                            if (players[target].health <= 0) {
                                players[target].is_dead = 1;
                                if (players[target].role == 'FP') {
                                    draw_cards(turn, 3);
                                } else if (players[target].role == 'ZP' && turn == 0) {
                                    players[0].hand_size = 0;
                                    players[0].has_crossbow = 0;
                                }
                            }
                        }
                    }
                }
                use_card(turn, 'W');
            } else if (players[turn].hand[i] == 'Z') {
                players[turn].has_crossbow = 1;
                use_card(turn, 'Z');
            }
        }
        turn = (turn + 1) % n;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        char role;
        scanf(" %c", &role);
        players[i].role = role;
        for (int j = 0; j < 4; j++) {
            scanf(" %c", &players[i].hand[j]);
        }
        players[i].hand_size = 4;
    }
    for (int i = 0; i < m; i++) {
        scanf(" %c", &deck[i]);
    }
    deck_size = m;
    init_game();
    play_game();
    return 0;
}