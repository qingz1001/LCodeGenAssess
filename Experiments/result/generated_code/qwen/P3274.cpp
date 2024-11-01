#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20000
#define MAX_M 200000
#define MAX_K 100000

typedef struct {
    int x;
    int y;
} Zombie;

int compare(const void *a, const void *b) {
    return ((Zombie *)a)->y - ((Zombie *)b)->y;
}

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    Zombie zombies[MAX_M];
    for (int i = 0; i < M; ++i) {
        scanf("%d %d", &zombies[i].x, &zombies[i].y);
    }

    qsort(zombies, M, sizeof(Zombie), compare);

    int total_killed = 0;
    for (int k = 0; k < K; ++k) {
        int max_killed = 0;
        int best_track = 0;
        for (int track = 1; track <= N; ++track) {
            int killed = 0;
            int pos = track;
            while (pos > 0 && pos <= N) {
                if (zombies[killed].y == track) {
                    if (zombies[killed].x >= pos) {
                        ++killed;
                    } else {
                        break;
                    }
                }
                pos += N / 2;
            }
            if (killed > max_killed) {
                max_killed = killed;
                best_track = track;
            }
        }
        printf("%d %d\n", best_track, max_killed);
        total_killed += max_killed;
    }
    printf("%d\n", total_killed);

    return 0;
}