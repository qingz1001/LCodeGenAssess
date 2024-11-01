#include <stdio.h>
#include <stdlib.h>

#define MAXN 200
#define MAXP 10

int main() {
    int N, M, P;
    scanf("%d %d %d", &N, &M, &P);

    int sum[MAXN + 1][MAXN + 1];
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= M; ++j) {
            scanf("%d", &sum[i][j]);
        }
    }

    int matrix[MAXN][MAXN];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (i == 0 || j == 0) {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = sum[i - 1][j - 1] - sum[i - 1][j] - sum[i][j - 1] + sum[i - 1][j - 1];
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}