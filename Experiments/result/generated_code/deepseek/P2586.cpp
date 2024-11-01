#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 8
#define MAX_M 8
#define MAX_S 20
#define MAX_T 200000

typedef struct {
    int x, y;
} Point;

typedef struct {
    int age;
    int level;
    int health;
    Point pos;
    int carrying_cake;
} Ant;

typedef struct {
    Point pos;
    int damage;
    int range;
} Tower;

int n, m, s, d, r, t;
Tower towers[MAX_S];
Ant ants[6];
int ant_count = 0;
int cake_pos = 0;
int game_over = 0;

void initialize_game() {
    for (int i = 0; i < 6; i++) {
        ants[i].age = 0;
        ants[i].level = (i / 6) + 1;
        ants[i].health = (int)(4 * pow(1.1, ants[i].level));
        ants[i].pos.x = 0;
        ants[i].pos.y = 0;
        ants[i].carrying_cake = 0;
    }
}

void spawn_ant() {
    if (ant_count < 6) {
        ants[ant_count].age = 0;
        ants[ant_count].level = (ant_count / 6) + 1;
        ants[ant_count].health = (int)(4 * pow(1.1, ants[ant_count].level));
        ants[ant_count].pos.x = 0;
        ants[ant_count].pos.y = 0;
        ants[ant_count].carrying_cake = 0;
        ant_count++;
    }
}

void move_ant(Ant *ant) {
    // Implement movement logic here
}

void attack_ants() {
    // Implement attack logic here
}

void update_pheromones() {
    // Implement pheromone update logic here
}

void simulate_game() {
    for (int time = 1; time <= t; time++) {
        if (game_over) break;
        spawn_ant();
        for (int i = 0; i < ant_count; i++) {
            move_ant(&ants[i]);
        }
        attack_ants();
        update_pheromones();
        for (int i = 0; i < ant_count; i++) {
            ants[i].age++;
        }
    }
}

void print_game_state() {
    if (game_over) {
        printf("Game over after %d seconds\n", t);
    } else {
        printf("The game is going on\n");
    }
    printf("%d\n", ant_count);
    for (int i = 0; i < ant_count; i++) {
        printf("%d %d %d %d %d\n", ants[i].age, ants[i].level, ants[i].health, ants[i].pos.x, ants[i].pos.y);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%d %d %d", &s, &d, &r);
    for (int i = 0; i < s; i++) {
        scanf("%d %d", &towers[i].pos.x, &towers[i].pos.y);
        towers[i].damage = d;
        towers[i].range = r;
    }
    scanf("%d", &t);

    initialize_game();
    simulate_game();
    print_game_state();

    return 0;
}