#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100
#define INF 1000000000

typedef struct {
    int x, y;
} Point;

int M, n, k;
Point weapons[MAXN];
Point bombs[MAXN];

int distance(Point p1, Point p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int can_destroy(int bomb_index) {
    for (int i = 0; i < M; i++) {
        if (weapons[i].y == 0 && distance(weapons[i], bombs[bomb_index]) <= k) {
            weapons[i].y = 1;
            if (i == M - 1) return 1;
        }
    }
    return 0;
}

int main() {
    scanf("%d %d %d", &M, &n, &k);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &weapons[i].x, &weapons[i].y);
        weapons[i].y = 0; // Initially all weapons are in defense mode
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &bombs[i].x, &bombs[i].y);
    }

    int used_bombs = 0;
    for (int i = 0; i < n; i++) {
        if (can_destroy(i)) {
            used_bombs++;
            break;
        }
    }

    printf("%d\n", used_bombs);

    return 0;
}