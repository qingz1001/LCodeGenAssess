#include <stdio.h>
#include <string.h>

#define MAX_N 10
#define MAX_M 2000

typedef struct {
    char role;
    int health;
    int max_health;
    char hand[MAX_M];
    int hand_size;
    int weapon;
    int identity_revealed;
} Pig;

Pig pigs[MAX_N];
char deck[MAX_M];
int deck_size;
int n, m;

void init_game() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        char role[5];
        scanf("%s", role);
        pigs[i].role = role[0];
        pigs[i].health = 4;
        pigs[i].max_health = 4;
        pigs[i].hand_size = 4;
        pigs[i].weapon = 0;
        pigs[i].identity_revealed = 0;
        for (int j = 0; j < 4; j++) {
            scanf(" %c", &pigs[i].hand[j]);
        }
    }
    for (int i = 0; i < m; i++) {
        scanf(" %c", &deck[i]);
    }
    deck_size = m;
}

void draw_cards(int pig_index, int count) {
    for (int i = 0; i < count; i++) {
        if (deck_size > 0) {
            pigs[pig_index].hand[pigs[pig_index].hand_size++] = deck[--deck_size];
        } else {
            pigs[pig_index].hand[pigs[pig_index].hand_size++] = deck[0];
        }
    }
}

void use_card(int pig_index, char card) {
    for (int i = 0; i < pigs[pig_index].hand_size; i++) {
        if (pigs[pig_index].hand[i] == card) {
            for (int j = i; j < pigs[pig_index].hand_size - 1; j++) {
                pigs[pig_index].hand[j] = pigs[pig_index].hand[j + 1];
            }
            pigs[pig_index].hand_size--;
            return;
        }
    }
}

void attack(int attacker, int target) {
    use_card(attacker, 'K');
    for (int i = 0; i < pigs[target].hand_size; i++) {
        if (pigs[target].hand[i] == 'D') {
            use_card(target, 'D');
            return;
        }
    }
    pigs[target].health--;
    if (pigs[target].health <= 0) {
        // Handle death
    }
}

void play_turn(int pig_index) {
    draw_cards(pig_index, 2);
    // Implement the logic for playing cards based on the rules
}

int main() {
    init_game();
    int current_pig = 0;
    while (1) {
        play_turn(current_pig);
        current_pig = (current_pig + 1) % n;
        // Check for game end conditions
    }
    return 0;
}