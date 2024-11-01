#include <stdio.h>
#include <string.h>

#define MOD 666623333
#define MAXN 2005

long long dp[MAXN][MAXN];
int n, x, q;
int l[MAXN], r[MAXN];

long long quick_pow(long long base, long long exp) {
    long long res = 1;
    while (exp) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

int main() {
    scanf("%d%d%d", &n, &x, &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d%d", &l[i], &r[i]);
    }

    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        dp[i][i] = x;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = (dp[i][j-1] * x + dp[i+1][j] * x - dp[i+1][j-1] * x + MOD) % MOD;
        }
    }

    long long ans = 0;
    for (int i = 1; i <= q; i++) {
        ans = (ans + dp[l[i]][r[i]]) % MOD;
    }

    long long inv = quick_pow(quick_pow(x, n), MOD - 2);
    ans = ans * inv % MOD;

    printf("%lld\n", ans);

    return 0;
}