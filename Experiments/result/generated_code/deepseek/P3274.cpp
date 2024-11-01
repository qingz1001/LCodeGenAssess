#include <stdio.h>
#include <stdlib.h>

#define MAXN 20000
#define MAXM 200000

typedef struct {
    int x, y;
} Zombie;

Zombie zombies[MAXM];
int zombieCount[MAXN + 1][MAXN + 1];
int maxZombies[MAXN + 1];

int compareZombies(const void *a, const void *b) {
    Zombie *z1 = (Zombie *)a;
    Zombie *z2 = (Zombie *)b;
    if (z1->y != z2->y) return z1->y - z2->y;
    return z1->x - z2->x;
}

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &zombies[i].x, &zombies[i].y);
    }

    qsort(zombies, M, sizeof(Zombie), compareZombies);

    for (int i = 0; i < M; i++) {
        zombieCount[zombies[i].y][zombies[i].x]++;
    }

    int totalKilled = 0;

    for (int round = 1; round <= K; round++) {
        int maxKill = 0;
        int bestTrack = 1;

        for (int track = 1; track <= N; track++) {
            int killCount = 0;
            for (int x = 1; x <= MAXN; x++) {
                killCount += zombieCount[track][x];
            }
            if (killCount > maxKill) {
                maxKill = killCount;
                bestTrack = track;
            }
        }

        printf("%d %d\n", bestTrack, maxKill);
        totalKilled += maxKill;

        for (int x = 1; x <= MAXN; x++) {
            zombieCount[bestTrack][x] = 0;
        }
    }

    printf("%d\n", totalKilled);

    return 0;
}