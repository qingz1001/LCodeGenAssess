#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX_N 101

long long dp[MAX_N][MAX_N];

long long solve(int n) {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            dp[i][j] = dp[i-1][j];
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i-1][j-1] * (i-1)) % MOD;
            }
        }
    }
    
    long long result = 0;
    for (int j = 0; j < n; j++) {
        result = (result + dp[n][j]) % MOD;
    }
    
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    
    long long ans = solve(n);
    printf("%lld\n", ans);
    
    return 0;
}