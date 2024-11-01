#include <stdio.h>
#include <stdlib.h>

#define MAX_N 6
#define MAX_M 6

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int T, N, M;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &M);
        int dp[MAX_N][MAX_M];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &dp[i][j]);
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = dp[i][j];
                } else if (i == 0) {
                    dp[i][j] += max(dp[i][j - 1], dp[i][j - 2]);
                } else if (j == 0) {
                    dp[i][j] += max(dp[i - 1][j], dp[i - 2][j]);
                } else {
                    dp[i][j] += max(max(dp[i - 1][j], dp[i - 2][j]), max(dp[i][j - 1], dp[i][j - 2]));
                }
            }
        }

        printf("%d\n", dp[N - 1][M - 1]);
    }
    return 0;
}