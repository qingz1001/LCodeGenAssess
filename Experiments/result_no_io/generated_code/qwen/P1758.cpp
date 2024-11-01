#include <stdio.h>
#include <stdlib.h>

#define MOD 1024523

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char top[n + 1], bottom[m + 1];
    scanf("%s%s", top, bottom);

    // Initialize DP table
    long long dp[501][501][2] = {0};
    dp[0][0][0] = 1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i > 0) {
                dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][0]) % MOD;
                dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][1]) % MOD;
            }
            if (j > 0) {
                dp[i][j][1] = (dp[i][j][1] + dp[i][j - 1][0]) % MOD;
                dp[i][j][1] = (dp[i][j][1] + dp[i][j - 1][1]) % MOD;
            }
        }
    }

    // Calculate the result
    long long result = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            result = (result + dp[i][j][0] * dp[i][j][1]) % MOD;
        }
    }

    printf("%lld\n", result);
    return 0;
}