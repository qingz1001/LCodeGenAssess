#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXN 100005

int n, a[MAXN];
long long dp[MAXN], sum[MAXN], ans;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= n; i++) {
        int last[MAXN] = {0};
        dp[i] = 1;
        sum[i] = (sum[i-1] + dp[i]) % MOD;
        
        for (int j = i-1; j >= 1; j--) {
            if (last[a[j]] == 0) {
                dp[j] = (sum[i-1] - sum[j-1] + MOD) % MOD;
            } else {
                dp[j] = (sum[i-1] - sum[last[a[j]]-1] + MOD) % MOD;
            }
            sum[j] = (sum[j-1] + dp[j]) % MOD;
            last[a[j]] = j;
        }
        
        for (int j = 1; j <= i; j++) {
            ans = (ans + dp[j]) % MOD;
        }
    }

    printf("%lld\n", ans);
    return 0;
}