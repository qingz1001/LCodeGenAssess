#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 8
#define MAX_S 20
#define MAX_T 200000
#define MAX_D 10000
#define MAX_R 15

typedef struct {
    int age;
    int level;
    int health;
    int x, y;
} Ant;

typedef struct {
    int x, y;
    int damage;
    int range;
} Tower;

Ant ants[MAX_N * MAX_N];
Tower towers[MAX_S];
int n, m, s, t, d, r;
int grid[MAX_N][MAX_N];

void initialize() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid[i][j] = 0;
        }
    }
}

void update_ant_positions(int time) {
    // Update ant positions based on the rules provided
    // This is a simplified version and does not include all the logic
    for (int i = 0; i < n * m; i++) {
        if (ants[i].health > 0) {
            ants[i].age++;
            // Move the ant according to the rules
            // ...
        }
    }
}

void apply_tower_damage(int time) {
    // Apply tower damage to ants within their range
    // This is a simplified version and does not include all the logic
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < n * m; j++) {
            if (ants[j].health > 0 && abs(ants[j].x - towers[i].x) <= towers[i].range && abs(ants[j].y - towers[i].y) <= towers[i].range) {
                ants[j].health -= towers[i].damage;
                if (ants[j].health < 0) {
                    ants[j].health = 0;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%d %d %d", &s, &d, &r);
    for (int i = 0; i < s; i++) {
        scanf("%d %d", &towers[i].x, &towers[i].y);
        towers[i].damage = d;
        towers[i].range = r;
    }
    scanf("%d", &t);

    initialize();

    for (int time = 0; time < t; time++) {
        update_ant_positions(time);
        apply_tower_damage(time);

        // Check if any ant has reached the goal or died
        int found = 0;
        for (int i = 0; i < n * m; i++) {
            if (ants[i].health == 0) {
                ants[i].health = 0;
            } else if (ants[i].x == 0 && ants[i].y == 0) {
                printf("Game over after %d seconds\n", time + 1);
                found = 1;
                break;
            }
        }

        if (found) {
            break;
        }
    }

    if (!found) {
        printf("The game is going on\n");
        for (int i = 0; i < n * m; i++) {
            if (ants[i].health > 0) {
                printf("%d %d %d %d %d\n", ants[i].age, ants[i].level, ants[i].health, ants[i].x, ants[i].y);
            }
        }
    }

    return 0;
}