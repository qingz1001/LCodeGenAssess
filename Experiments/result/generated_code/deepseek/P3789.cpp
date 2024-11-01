#include <stdio.h>
#include <string.h>

#define MOD 998244353
#define MAXK 100000

typedef long long ll;

ll dp[2][MAXK + 1];

void solve(ll n, int k) {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    dp[1][0] = 1;

    for (int i = 1; i <= k; i++) {
        dp[0][i] = (dp[0][i - 1] * 2) % MOD;
    }

    for (int i = 1; i <= k; i++) {
        dp[1][i] = (dp[1][i - 1] * 2 + dp[0][i - 1]) % MOD;
    }

    for (int i = 2; i <= k; i++) {
        dp[1][i] = (dp[1][i] + dp[1][i - 2]) % MOD;
    }

    ll result[MAXK + 1];
    result[0] = dp[1][0];

    for (int i = 1; i <= k; i++) {
        result[i] = (dp[1][i] - dp[1][i - 1] + MOD) % MOD;
    }

    for (int i = 0; i <= k; i++) {
        printf("%lld ", result[i]);
    }
    printf("\n");
}

int main() {
    ll n;
    int k;
    scanf("%lld %d", &n, &k);
    solve(n, k);
    return 0;
}