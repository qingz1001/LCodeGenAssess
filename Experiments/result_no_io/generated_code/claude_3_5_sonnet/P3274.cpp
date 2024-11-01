#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20000
#define MAX_M 200000
#define MAX_X 1000000

typedef struct {
    int x, y;
} Zombie;

Zombie zombies[MAX_M];
int zombieCount[MAX_N + 1][MAX_X + 1];
int N, M, K;

int compare(const void* a, const void* b) {
    Zombie* za = (Zombie*)a;
    Zombie* zb = (Zombie*)b;
    if (za->x != zb->x) return za->x - zb->x;
    return za->y - zb->y;
}

int simulateNut(int lane) {
    int killed = 0;
    int x = 0, y = lane;
    int dx = 1, dy = (y <= N / 2) ? 1 : -1;

    while (1) {
        while (x <= MAX_X && zombieCount[y][x] == 0) x++;
        if (x > MAX_X) break;

        killed++;
        zombieCount[y][x]--;
        if (zombieCount[y][x] == 0) {
            for (int i = 0; i < M; i++) {
                if (zombies[i].x == x && zombies[i].y == y) {
                    zombies[i].x = MAX_X + 1;
                    break;
                }
            }
        }

        x += dx;
        y += dy;

        if (y == 0 || y == N + 1) {
            dy = -dy;
            y += 2 * dy;
        }
    }

    return killed;
}

int main() {
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &zombies[i].x, &zombies[i].y);
        zombieCount[zombies[i].y][zombies[i].x]++;
    }

    qsort(zombies, M, sizeof(Zombie), compare);

    int totalKilled = 0;

    for (int round = 0; round < K; round++) {
        int bestLane = 1, maxKilled = 0;

        for (int lane = 1; lane <= N; lane++) {
            int killed = simulateNut(lane);
            if (killed > maxKilled) {
                maxKilled = killed;
                bestLane = lane;
            }
        }

        if (maxKilled == 0) break;

        printf("%d %d\n", bestLane, maxKilled);
        totalKilled += maxKilled;

        simulateNut(bestLane);
    }

    printf("%d\n", totalKilled);

    return 0;
}