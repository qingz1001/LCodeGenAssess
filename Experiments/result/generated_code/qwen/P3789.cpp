#include <stdio.h>
#define MOD 998244353

typedef long long ll;

int main() {
    ll n, k;
    scanf("%lld %lld", &n, &k);

    if (k > n) {
        for (ll i = 0; i <= k; ++i) printf("0 ");
        return 0;
    }

    ll dp[n + 1][k + 1];
    for (ll i = 0; i <= n; ++i) for (ll j = 0; j <= k; ++j) dp[i][j] = 0;

    dp[0][0] = 1;
    for (ll i = 1; i <= n; ++i) {
        for (ll j = 0; j <= k; ++j) {
            dp[i][j] = ((dp[i - 1][j] * 2) % MOD + (j > 0 ? dp[i - 1][j - 1] : 0)) % MOD;
        }
    }

    for (ll i = 0; i <= k; ++i) printf("%lld ", dp[n][i]);
    printf("\n");

    return 0;
}