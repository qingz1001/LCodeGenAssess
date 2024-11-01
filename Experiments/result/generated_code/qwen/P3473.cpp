#include <stdio.h>

#define MOD 1000000007

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int x, y;
    scanf("%d %d", &x, &y);

    int dp[n+1][m+1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
        }
    }

    dp[1][1] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == x && j == y) continue;
            if (dp[i][j] == 0) continue;

            if (i > 1) dp[i-1][j] = (dp[i-1][j] + dp[i][j]) % MOD;
            if (j > 1) dp[i][j-1] = (dp[i][j-1] + dp[i][j]) % MOD;
        }
    }

    printf("%d\n", dp[x][y]);

    return 0;
}