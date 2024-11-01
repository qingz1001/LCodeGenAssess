#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 100
#define MOD 1000000007

typedef long long ll;

ll fac[MAX_N + 1], inv[MAX_N + 1];
ll dp[MAX_N + 1][MAX_N * MAX_N + 1];
int n, m, k;

ll quick_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void init() {
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i-1] * i % MOD;
        inv[i] = quick_pow(fac[i], MOD - 2);
    }
}

ll C(int n, int m) {
    if (m > n) return 0;
    return fac[n] * inv[m] % MOD * inv[n-m] % MOD;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    init();

    memset(dp, 0, sizeof(dp));
    dp[1][0] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= (n-1)*n/2; j++) {
            for (int k = 0; k < i; k++) {
                int val = j - k*(i-k-1) - (i-k-1)*(k+1);
                if (val >= 0) {
                    dp[i][j] = (dp[i][j] + dp[i-1][val] * C(i-1, k)) % MOD;
                }
            }
        }
    }

    ll total = 0;
    for (int i = m; i <= (n-1)*n/2; i++) {
        total = (total + dp[n][i]) % MOD;
    }

    double ans = (double)total / fac[n];
    printf("%.*f\n", k, ans + 1e-10);

    return 0;
}