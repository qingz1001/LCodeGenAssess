#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

typedef long long ll;

int main() {
    int n, m, s_len;
    scanf("%d %d %d", &n, &m, &s_len);
    
    if (s_len == 0) {
        printf("1\n");
        return 0;
    }
    
    ll dp[s_len + 1][n + 1];
    for (int i = 0; i <= s_len; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = 0;
        }
    }
    
    dp[0][0] = 1;
    for (int i = 0; i < s_len; ++i) {
        for (int j = 0; j <= n - s_len + i; ++j) {
            dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % MOD;
            dp[i][j + 1] = (dp[i][j + 1] + dp[i][j] * (m - 1)) % MOD;
        }
    }
    
    printf("%lld\n", dp[s_len][n]);
    
    return 0;
}