#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 9
#define MAX_S 21
#define MAX_T 200001

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

int n, m, s, t, d, r;
Ant ants[MAX_T];
Tower towers[MAX_S];
int pheromone[MAX_N][MAX_N];

void init() {
    memset(pheromone, 0, sizeof(pheromone));
}

int in_bounds(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int find_next_direction(Ant *ant, int dx[], int dy[]) {
    int max_pheromone = -1;
    int next_x = ant->x, next_y = ant->y;
    for (int i = 0; i < 4; i++) {
        int nx = ant->x + dx[i], ny = ant->y + dy[i];
        if (in_bounds(nx, ny) && !pheromone[nx][ny]) {
            if (max_pheromone == -1 || pheromone[nx][ny] > max_pheromone) {
                max_pheromone = pheromone[nx][ny];
                next_x = nx, next_y = ny;
            }
        }
    }
    if (next_x != ant->x || next_y != ant->y) {
        return i;
    }
    for (int i = 0; i < 4; i++) {
        int nx = ant->x + dx[(i + 1) % 4], ny = ant->y + dy[(i + 1) % 4];
        if (in_bounds(nx, ny) && !pheromone[nx][ny]) {
            return (i + 1) % 4;
        }
    }
    return -1;
}

void move_ants() {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    for (int i = 0; i < s; i++) {
        if (ants[i].health <= 0) continue;
        ants[i].age++;
        ants[i].health -= d;
        if (ants[i].health <= 0) {
            ants[i].health = 0;
            continue;
        }
        int dir = find_next_direction(&ants[i], dx, dy);
        if (dir != -1) {
            ants[i].x += dx[dir];
            ants[i].y += dy[dir];
            pheromone[ants[i].x][ants[i].y] += ants[i].age % 5 ? 2 : 5;
        }
    }
}

void attack_towers() {
    for (int i = 0; i < s; i++) {
        if (ants[i].health <= 0) continue;
        int min_distance = m + n;
        int target_index = -1;
        for (int j = 0; j < s; j++) {
            if (j == i) continue;
            int distance = abs(ants[j].x - ants[i].x) + abs(ants[j].y - ants[i].y);
            if (distance <= towers[i].range && distance < min_distance) {
                min_distance = distance;
                target_index = j;
            }
        }
        if (target_index != -1) {
            ants[target_index].health -= towers[i].damage;
            if (ants[target_index].health <= 0) {
                ants[target_index].health = 0;
            }
        }
    }
}

int check_game_over() {
    for (int i = 0; i < s; i++) {
        if (ants[i].x == 0 && ants[i].y == 0) {
            printf("Game over after %d seconds\n", ants[i].age);
            return 1;
        }
        if (ants[i].x == n && ants[i].y == m) {
            printf("Game over after %d seconds\n", ants[i].age);
            return 1;
        }
    }
    return 0;
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%d %d %d", &s, &d, &r);
    for (int i = 0; i < s; i++) {
        scanf("%d %d", &towers[i].x, &towers[i].y);
    }
    scanf("%d", &t);

    init();
    for (int i = 0; i < t; i++) {
        if (i < s) {
            ants[i].age = 0;
            ants[i].level = (i / 6) + 1;
            ants[i].health = 4 * (int)(pow(1.1, ants[i].level - 1));
            ants[i].x = 0;
            ants[i].y = 0;
        }
        move_ants();
        attack_towers();
        if (check_game_over()) {
            break;
        }
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                pheromone[j][k]--;
            }
        }
    }

    if (!check_game_over()) {
        printf("The game is going on\n");
        printf("%d\n", s);
        for (int i = 0; i < s; i++) {
            if (ants[i].health > 0) {
                printf("%d %d %d %d %d\n", ants[i].age, ants[i].level, ants[i].health, ants[i].x, ants[i].y);
            }
        }
    }

    return 0;
}