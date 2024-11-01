#include <stdio.h>
#include <stdlib.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, M;
        scanf("%d %d", &N, &M);
        int matrix[N][M];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }

        int dp[N][M][2];
        dp[0][0][0] = matrix[0][0];
        dp[0][0][1] = 0;
        for (int i = 1; i < M; i++) {
            dp[0][i][0] = matrix[0][i] + dp[0][i-1][1];
            dp[0][i][1] = dp[0][i-1][0];
        }
        for (int i = 1; i < N; i++) {
            dp[i][0][0] = matrix[i][0] + dp[i-1][0][1];
            dp[i][0][1] = dp[i-1][0][0];
        }
        for (int i = 1; i < N; i++) {
            for (int j = 1; j < M; j++) {
                dp[i][j][0] = matrix[i][j] + (dp[i-1][j][1] > dp[i][j-1][1] ? dp[i-1][j][1] : dp[i][j-1][1]);
                dp[i][j][1] = (dp[i-1][j][0] > dp[i][j-1][0] ? dp[i-1][j][0] : dp[i][j-1][0]) - matrix[i][j];
            }
        }

        printf("%d\n", dp[N-1][M-1][0]);
    }
    return 0;
}