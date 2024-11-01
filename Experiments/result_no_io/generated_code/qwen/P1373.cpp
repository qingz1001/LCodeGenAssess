#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    long long **dp = (long long **)malloc((n + 1) * sizeof(long long *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (long long *)malloc((m + 1) * sizeof(long long));
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
        }
    }
    
    dp[1][1] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == 1 && j == 1) continue;
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
        }
    }
    
    printf("%lld\n", dp[n][m]);
    
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return 0;
}