#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_M 100
#define MAX_N 100

typedef struct {
    int x, y;
} Point;

int M, n, k;
Point weapons[MAX_M];
Point bombs[MAX_N];
int used[MAX_N];

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int canDestroy(int weaponIndex, int bombIndex) {
    return distance(weapons[weaponIndex], bombs[bombIndex]) <= k;
}

int dfs(int weaponIndex, int bombCount) {
    if (weaponIndex == M) return 1; // All weapons destroyed
    for (int i = 0; i < n; i++) {
        if (!used[i] && canDestroy(weaponIndex, i)) {
            used[i] = 1;
            if (dfs(weaponIndex + 1, bombCount + 1)) return 1;
            used[i] = 0;
        }
    }
    return 0;
}

int main() {
    scanf("%d %d %d", &M, &n, &k);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &weapons[i].x, &weapons[i].y);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &bombs[i].x, &bombs[i].y);
    }

    for (int i = 0; i < n; i++) {
        used[i] = 0;
    }

    int bombCount = 0;
    while (!dfs(0, 0)) {
        bombCount++;
    }

    printf("%d\n", bombCount);
    return 0;
}