#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXN 100005

long long dp[MAXN], sum[MAXN], ans;
int n, a[MAXN], last[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    memset(last, 0, sizeof(last));
    
    for (int i = 1; i <= n; i++) {
        dp[i] = (dp[i-1] * 2 % MOD + 1) % MOD;
        if (last[a[i]]) {
            dp[i] = (dp[i] - dp[last[a[i]]-1] + MOD) % MOD;
        }
        last[a[i]] = i;
        sum[i] = (sum[i-1] + dp[i]) % MOD;
        ans = (ans + sum[i]) % MOD;
    }
    
    printf("%lld\n", ans);
    
    return 0;
}