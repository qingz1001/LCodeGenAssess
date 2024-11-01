#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_M 100
#define MAX_N 100

typedef struct {
    int x, y;
} Point;

Point weapons[MAX_M];
Point bombs[MAX_N];
int M, n, k;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int canDestroy(int bombIndex, int weaponIndex) {
    return distance(bombs[bombIndex], weapons[weaponIndex]) <= k;
}

int solve() {
    int usedBombs[MAX_M] = {0};
    int currentWeapon = 0;
    int bombCount = 0;

    while (currentWeapon < M) {
        int bestBomb = -1;
        int maxDestroyed = 0;

        for (int i = 0; i < n; i++) {
            if (usedBombs[i]) continue;
            int destroyed = 0;
            for (int j = currentWeapon; j < M; j++) {
                if (canDestroy(i, j)) {
                    destroyed++;
                } else {
                    break;
                }
            }
            if (destroyed > maxDestroyed) {
                maxDestroyed = destroyed;
                bestBomb = i;
            }
        }

        if (bestBomb == -1) return -1;

        usedBombs[bestBomb] = 1;
        currentWeapon += maxDestroyed;
        bombCount++;
    }

    return bombCount;
}

int main() {
    scanf("%d %d %d", &M, &n, &k);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &weapons[i].x, &weapons[i].y);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &bombs[i].x, &bombs[i].y);
    }

    int result = solve();
    printf("%d\n", result);

    return 0;
}