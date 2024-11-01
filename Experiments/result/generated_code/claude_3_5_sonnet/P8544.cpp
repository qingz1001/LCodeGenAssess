#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAXN 500005
#define MAXM 500005

long long a[MAXN], b[MAXM];
long long dp[2][MAXM];
int n, m, t;

int main() {
    scanf("%d %d %d", &n, &m, &t);
    
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    
    for(int i = 1; i <= m; i++) {
        scanf("%lld", &b[i]);
    }
    
    memset(dp, 0x3f, sizeof(dp));
    
    for(int j = 1; j <= m; j++) {
        dp[1][j] = 0;
    }
    
    int curr = 1, prev = 0;
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            dp[curr][j] = 0x3f3f3f3f3f3f3f3fLL;
            for(int k = 1; k <= m; k++) {
                if(j == k) continue;
                long long cost = 0;
                for(int l = (j < k ? j : k); l <= (j > k ? j : k); l++) {
                    cost = (cost + a[i] * b[l]) % MOD;
                }
                dp[curr][j] = (dp[curr][j] < dp[prev][k] + cost) ? dp[curr][j] : dp[prev][k] + cost;
            }
        }
        curr ^= 1;
        prev ^= 1;
    }
    
    long long ans = 0x3f3f3f3f3f3f3f3fLL;
    for(int j = 1; j <= m; j++) {
        ans = (ans < dp[prev][j]) ? ans : dp[prev][j];
    }
    
    printf("%lld\n", ans);
    
    return 0;
}