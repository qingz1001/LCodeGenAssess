#include <stdio.h>
#include <string.h>

#define MAX_N 6
#define MAX_M 6

int T, N, M;
int matrix[MAX_N][MAX_M];
int dp[MAX_N][MAX_M][1 << MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int solve() {
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < (1 << M); j++) {
            if ((j & (j << 1)) || (j & (j >> 1))) continue;

            if (i == 0) {
                int sum = 0;
                for (int k = 0; k < M; k++) {
                    if (j & (1 << k)) sum += matrix[i][k];
                }
                dp[i][M-1][j] = sum;
            } else {
                for (int k = 0; k < (1 << M); k++) {
                    if ((k & j) || (k & (j << 1)) || (k & (j >> 1))) continue;

                    int sum = 0;
                    for (int l = 0; l < M; l++) {
                        if (j & (1 << l)) sum += matrix[i][l];
                    }

                    for (int l = 0; l < M; l++) {
                        dp[i][l][j] = max(dp[i][l][j], dp[i-1][M-1][k] + sum);
                    }
                }
            }
        }
    }

    int result = 0;
    for (int j = 0; j < (1 << M); j++) {
        result = max(result, dp[N-1][M-1][j]);
    }
    return result;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }
        printf("%d\n", solve());
    }
    return 0;
}