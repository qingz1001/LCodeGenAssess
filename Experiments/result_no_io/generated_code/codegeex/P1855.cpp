#include <stdio.h>

int main() {
    int n, M, T;
    scanf("%d %d %d", &n, &M, &T);

    int m[101], t[101];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &m[i], &t[i]);
    }

    int dp[201][201];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= M; j++) {
            for (int k = 0; k <= T; k++) {
                if (i == 0 || j < m[i-1] || k < t[i-1]) {
                    dp[i][j] = dp[i-1][j];
                } else {
                    dp[i][j] = (dp[i-1][j] > dp[i-1][j-m[i-1]] + 1) ? dp[i-1][j] : dp[i-1][j-m[i-1]] + 1;
                }
            }
        }
    }

    printf("%d\n", dp[n][M]);
    return 0;
}