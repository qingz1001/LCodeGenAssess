#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 8
#define MAX_M 8
#define MAX_ANTS 1000
#define MAX_TOWERS 20
#define DIRECTIONS 4

const int dx[4] = {0, 1, 0, -1};  // 东南西北
const int dy[4] = {1, 0, -1, 0};

int n, m, s, d, r, t;
int map[MAX_N+1][MAX_M+1];
int pheromone[MAX_N+1][MAX_M+1];
int tower_x[MAX_TOWERS], tower_y[MAX_TOWERS];

typedef struct {
    int age;
    int level;
    int hp;
    int x, y;
    int has_cake;
} Ant;

Ant ants[MAX_ANTS];
int ant_count = 0;

int cake_x, cake_y;
int cake_carried = 0;

int compare_ants(const void *a, const void *b) {
    return ((Ant*)b)->age - ((Ant*)a)->age;
}

int is_valid(int x, int y) {
    return x >= 0 && x <= n && y >= 0 && y <= m && map[x][y] == 0;
}

void spawn_ant() {
    if (ant_count < 6 && map[0][0] == 0) {
        ants[ant_count].age = 0;
        ants[ant_count].level = ant_count / 6 + 1;
        ants[ant_count].hp = floor(4 * pow(1.1, ants[ant_count].level));
        ants[ant_count].x = 0;
        ants[ant_count].y = 0;
        ants[ant_count].has_cake = 0;
        ant_count++;
    }
}

void move_ant(int i) {
    Ant *ant = &ants[i];
    int max_pheromone = -1;
    int best_dir = -1;

    for (int dir = 0; dir < DIRECTIONS; dir++) {
        int nx = ant->x + dx[dir];
        int ny = ant->y + dy[dir];
        if (is_valid(nx, ny) && (nx != ant->x || ny != ant->y || (ant->x == 0 && ant->y == 0))) {
            if (pheromone[nx][ny] > max_pheromone) {
                max_pheromone = pheromone[nx][ny];
                best_dir = dir;
            }
        }
    }

    if (best_dir == -1) return;

    if (ant->age % 5 == 0) {
        int original_dir = best_dir;
        for (int i = 0; i < 4; i++) {
            int dir = (original_dir - i + 4) % 4;
            int nx = ant->x + dx[dir];
            int ny = ant->y + dy[dir];
            if (is_valid(nx, ny)) {
                best_dir = dir;
                break;
            }
        }
    }

    ant->x += dx[best_dir];
    ant->y += dy[best_dir];

    if (ant->x == cake_x && ant->y == cake_y && !cake_carried) {
        ant->has_cake = 1;
        cake_carried = 1;
        ant->hp = fmin(ant->hp + floor(4 * pow(1.1, ant->level) / 2), floor(4 * pow(1.1, ant->level)));
    }
}

void attack_ants() {
    for (int i = 0; i < s; i++) {
        int tx = tower_x[i], ty = tower_y[i];
        int target = -1;
        double min_dist = r + 1;

        for (int j = 0; j < ant_count; j++) {
            double dist = sqrt(pow(ants[j].x - tx, 2) + pow(ants[j].y - ty, 2));
            if (dist <= r) {
                if (ants[j].has_cake || (target == -1 || dist < min_dist)) {
                    target = j;
                    min_dist = dist;
                }
            }
        }

        if (target != -1) {
            for (int j = 0; j < ant_count; j++) {
                if (j == target || (ants[j].x - tx) * (ants[target].y - ty) == (ants[j].y - ty) * (ants[target].x - tx)) {
                    ants[j].hp -= d;
                }
            }
        }
    }

    for (int i = ant_count - 1; i >= 0; i--) {
        if (ants[i].hp <= 0) {
            if (ants[i].has_cake) {
                cake_carried = 0;
                cake_x = n;
                cake_y = m;
            }
            ants[i] = ants[--ant_count];
        }
    }
}

void update_pheromone() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (pheromone[i][j] > 0) pheromone[i][j]--;
        }
    }

    for (int i = 0; i < ant_count; i++) {
        pheromone[ants[i].x][ants[i].y] += ants[i].has_cake ? 5 : 2;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%d %d %d", &s, &d, &r);

    for (int i = 0; i < s; i++) {
        scanf("%d %d", &tower_x[i], &tower_y[i]);
        map[tower_x[i]][tower_y[i]] = 1;
    }

    scanf("%d", &t);

    cake_x = n;
    cake_y = m;

    for (int second = 1; second <= t; second++) {
        spawn_ant();

        for (int i = 0; i < ant_count; i++) {
            move_ant(i);
            ants[i].age++;
        }

        attack_ants();
        update_pheromone();

        for (int i = 0; i < ant_count; i++) {
            if (ants[i].has_cake && ants[i].x == 0 && ants[i].y == 0) {
                printf("Game over after %d seconds\n", second);
                qsort(ants, ant_count, sizeof(Ant), compare_ants);
                printf("%d\n", ant_count);
                for (int j = 0; j < ant_count; j++) {
                    printf("%d %d %d %d %d\n", ants[j].age, ants[j].level, ants[j].hp, ants[j].x, ants[j].y);
                }
                return 0;
            }
        }
    }

    printf("The game is going on\n");
    qsort(ants, ant_count, sizeof(Ant), compare_ants);
    printf("%d\n", ant_count);
    for (int i = 0; i < ant_count; i++) {
        printf("%d %d %d %d %d\n", ants[i].age, ants[i].level, ants[i].hp, ants[i].x, ants[i].y);
    }

    return 0;
}