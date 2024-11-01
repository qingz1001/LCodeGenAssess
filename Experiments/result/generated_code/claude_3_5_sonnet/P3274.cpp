#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20000
#define MAX_M 200000
#define MAX_X 1000000

typedef struct {
    int x, y;
} Zombie;

int N, M, K;
Zombie zombies[MAX_M];
int count[MAX_N + 1][MAX_X + 1];
int max_x = 0;

int compare(const void* a, const void* b) {
    Zombie* za = (Zombie*)a;
    Zombie* zb = (Zombie*)b;
    if (za->x != zb->x) return za->x - zb->x;
    return za->y - zb->y;
}

int simulate(int start_row) {
    int killed = 0;
    int row = start_row, col = 0;
    int direction = (row <= N / 2) ? 1 : -1;

    while (1) {
        while (col <= max_x && count[row][col] == 0) col++;
        if (col > max_x) break;

        killed++;
        count[row][col]--;
        col++;

        row += direction;
        if (row == 0 || row == N + 1) {
            direction = -direction;
            row += 2 * direction;
        }
    }

    return killed;
}

int main() {
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &zombies[i].x, &zombies[i].y);
        if (zombies[i].x > max_x) max_x = zombies[i].x;
    }

    qsort(zombies, M, sizeof(Zombie), compare);

    for (int i = 0; i < M; i++) {
        count[zombies[i].y][zombies[i].x]++;
    }

    int total_killed = 0;

    for (int k = 0; k < K; k++) {
        int best_row = 1, max_killed = 0;

        for (int i = 1; i <= N; i++) {
            int killed = simulate(i);
            if (killed > max_killed) {
                max_killed = killed;
                best_row = i;
            }
        }

        printf("%d %d\n", best_row, max_killed);
        total_killed += max_killed;

        if (max_killed == 0) break;

        for (int i = 0; i < M; i++) {
            count[zombies[i].y][zombies[i].x]++;
        }

        simulate(best_row);
    }

    printf("%d\n", total_killed);

    return 0;
}