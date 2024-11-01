#include <stdio.h>
#include <string.h>

#define MOD 666623333
#define MAXN 2005

long long qpow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int n, x, q;
int l[MAXN], r[MAXN];
long long dp[MAXN][MAXN];
long long inv[MAXN];

int main() {
    scanf("%d%d%d", &n, &x, &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d%d", &l[i], &r[i]);
    }

    inv[1] = 1;
    for (int i = 2; i <= x; i++) {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }

    for (int i = 1; i <= n; i++) {
        dp[i][i] = x;
        for (int j = i + 1; j <= n; j++) {
            dp[i][j] = dp[i][j-1] * (x - 1) % MOD * inv[x] % MOD;
        }
    }

    long long ans = 0;
    for (int k = 1; k <= x; k++) {
        long long prob = 1;
        for (int i = 1; i <= q; i++) {
            prob = prob * (dp[l[i]][r[i]] - dp[l[i]][r[i]] * qpow(k - 1, r[i] - l[i] + 1) % MOD * inv[k] % MOD + MOD) % MOD;
        }
        ans = (ans + k * prob) % MOD;
    }

    printf("%lld\n", ans);
    return 0;
}