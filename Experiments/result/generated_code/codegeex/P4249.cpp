#include <stdio.h>
#include <string.h>

int main() {
    int N;
    scanf("%d", &N);

    int win[N][N], lose[N][N], draw[N][N];
    memset(win, 0, sizeof(win));
    memset(lose, 0, sizeof(lose));
    memset(draw, 0, sizeof(draw));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int result;
            scanf("%d", &result);
            if (result == 1) {
                win[i][j] = 1;
                lose[j][i] = 1;
            } else if (result == 0) {
                lose[i][j] = 1;
                win[j][i] = 1;
            } else if (result == 2) {
                draw[i][j] = 1;
                draw[j][i] = 1;
            }
        }
    }

    int totalDraws = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (draw[i][j]) {
                totalDraws++;
            }
        }
    }

    printf("%d\n", totalDraws);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                printf("0 ");
            } else if (win[i][j]) {
                printf("1 ");
            } else if (lose[i][j]) {
                printf("0 ");
            } else if (draw[i][j]) {
                // Arbitrarily decide one outcome
                printf("1 ");
                win[i][j] = 1;
                lose[j][i] = 1;
            }
        }
        printf("\n");
    }

    return 0;
}