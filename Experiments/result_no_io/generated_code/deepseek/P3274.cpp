#include <stdio.h>
#include <stdlib.h>

#define MAXN 20000
#define MAXM 200000
#define MAXK 100000

typedef struct {
    int x, y;
} Zombie;

Zombie zombies[MAXM];
int zombie_count[MAXN + 1][MAXN + 1];
int max_zombies[MAXN + 1];

int compare(const void *a, const void *b) {
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

    qsort(zombies, M, sizeof(Zombie), compare);

    for (int i = 0; i < M; i++) {
        zombie_count[zombies[i].y][zombies[i].x]++;
    }

    int total_killed = 0;

    for (int k = 0; k < K; k++) {
        int max_kill = 0;
        int best_track = 1;

        for (int i = 1; i <= N; i++) {
            int kill_count = 0;
            for (int j = 1; j <= MAXN; j++) {
                kill_count += zombie_count[i][j];
            }
            if (kill_count > max_kill) {
                max_kill = kill_count;
                best_track = i;
            }
        }

        printf("%d %d\n", best_track, max_kill);
        total_killed += max_kill;

        for (int j = 1; j <= MAXN; j++) {
            zombie_count[best_track][j] = 0;
        }
    }

    printf("%d\n", total_killed);

    return 0;
}