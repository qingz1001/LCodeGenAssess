#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAX_N 500005
#define MAX_M 500005

long long a[MAX_N], b[MAX_M];
long long dp[2][MAX_M];
int n, m, t;

long long min(long long a, long long b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &m, &t);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    
    for (int i = 1; i <= m; i++) {
        scanf("%lld", &b[i]);
    }
    
    memset(dp, 0x3f, sizeof(dp));
    for (int j = 1; j <= m; j++) {
        dp[1][j] = 0;
    }
    
    int cur = 1, pre = 0;
    for (int i = 1; i <= n; i++) {
        cur ^= 1;
        pre ^= 1;
        
        for (int j = 1; j <= m; j++) {
            dp[cur][j] = 0x3f3f3f3f3f3f3f3fLL;
            for (int k = 1; k <= m; k++) {
                if (j == k) continue;
                long long cost = 0;
                for (int p = min(j, k); p <= (j > k ? j : k); p++) {
                    cost = (cost + a[i] * b[p]) % MOD;
                }
                dp[cur][j] = min(dp[cur][j], dp[pre][k] + cost);
            }
        }
    }
    
    long long ans = 0x3f3f3f3f3f3f3f3fLL;
    for (int j = 1; j <= m; j++) {
        ans = min(ans, dp[cur][j]);
    }
    
    printf("%lld\n", ans);
    
    return 0;
}