#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_M 100
#define MAX_N 100
#define K_MAX 1000

int M, N, K;
int weapons[MAX_M][2];
int bombs[MAX_N][2];

int distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int can_destroy(int bomb_index) {
    for (int i = 0; i < M; i++) {
        if (distance(bombs[bomb_index][0], bombs[bomb_index][1], weapons[i][0], weapons[i][1]) <= K) {
            if (i == 0) {
                return 1;
            } else if (weapons[i-1][0] != 0 || weapons[i-1][1] != 0) {
                weapons[i-1][0] = 0;
                weapons[i-1][1] = 0;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d %d %d", &M, &N, &K);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &weapons[i][0], &weapons[i][1]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &bombs[i][0], &bombs[i][1]);
    }

    int bomb_index = 0;
    while (bomb_index < N && M > 0) {
        if (can_destroy(bomb_index)) {
            M--;
        }
        bomb_index++;
    }

    printf("%d\n", bomb_index);

    return 0;
}