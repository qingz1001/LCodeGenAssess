#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353
#define MAXN 100005

typedef long long ll;

ll dp[MAXN][26];
ll sum[MAXN];

ll mod_add(ll a, ll b) {
    return (a + b) % MOD;
}

ll mod_sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

int main() {
    int n;
    scanf("%d", &n);
    int a[MAXN];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    memset(dp, 0, sizeof(dp));
    memset(sum, 0, sizeof(sum));

    ll total_sum = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 26; j++) {
            dp[i][j] = sum[j];
        }
        dp[i][a[i]] = mod_add(dp[i][a[i]], i);

        for (int j = 0; j < 26; j++) {
            sum[j] = mod_add(sum[j], dp[i][j]);
        }

        for (int j = 0; j < 26; j++) {
            total_sum = mod_add(total_sum, dp[i][j]);
        }
    }

    printf("%lld\n", total_sum);

    return 0;
}