#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 101

typedef struct {
    int x, y;
} Point;

Point weapons[MAX_N];
Point bombs[MAX_N];
int M, n, k;
int used[MAX_N] = {0};
int destroyed[MAX_N] = {0};

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int can_destroy(int bomb, int weapon) {
    return distance(bombs[bomb], weapons[weapon]) <= k;
}

int find_best_bomb(int current_weapon) {
    int best_bomb = -1;
    int max_destroyed = -1;

    for (int i = 0; i < n; i++) {
        if (used[i]) continue;

        int count = 0;
        for (int j = current_weapon; j < M; j++) {
            if (destroyed[j]) continue;
            if (can_destroy(i, j)) count++;
        }

        if (count > max_destroyed) {
            max_destroyed = count;
            best_bomb = i;
        }
    }

    return best_bomb;
}

int main() {
    scanf("%d %d %d", &M, &n, &k);

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &weapons[i].x, &weapons[i].y);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &bombs[i].x, &bombs[i].y);
    }

    int bombs_used = 0;
    int current_weapon = 0;

    while (current_weapon < M) {
        int best_bomb = find_best_bomb(current_weapon);
        if (best_bomb == -1) break;

        used[best_bomb] = 1;
        bombs_used++;

        for (int i = current_weapon; i < M; i++) {
            if (!destroyed[i] && can_destroy(best_bomb, i)) {
                destroyed[i] = 1;
                current_weapon = i + 1;
            }
        }
    }

    printf("%d\n", bombs_used);

    return 0;
}