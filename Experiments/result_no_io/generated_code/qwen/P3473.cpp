#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int x, y;
    scanf("%d %d", &x, &y);

    // Initialize DP table
    long long dp[n+1][m+1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
        }
    }

    // Starting point
    dp[1][1] = 1;

    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == 1 && j == 1) continue; // Skip starting point
            dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
        }
    }

    // Output result
    printf("%lld\n", dp[x][y]);

    return 0;
}