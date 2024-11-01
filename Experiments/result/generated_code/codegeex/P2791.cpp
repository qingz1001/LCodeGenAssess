#include <stdio.h>
#include <string.h>
#define MOD 998244353
#define MAXN 200000

typedef long long ll;

ll fac[MAXN + 5], ifac[MAXN + 5], inv[MAXN + 5], pre[MAXN + 5], suf[MAXN + 5], c[MAXN + 5][MAXN + 5];

int main() {
    int n, m, s, l;
    scanf("%d%d%d%d", &n, &m, &s, &l);

    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[n] = pow(fac[n], MOD - 2, MOD);
    for (int i = n - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
    for (int i = 0; i <= n; i++) c[i][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + ifac[i] * inv[i] % MOD;
    for (int i = n; i >= 1; i--) suf[i] = suf[i + 1] + ifac[i] * inv[i] % MOD;
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + pre[i];
    for (int i = n; i >= 1; i--) suf[i] = suf[i + 1] + suf[i];

    while (s--) {
        int ni, mi, ki;
        scanf("%d%d%d", &ni, &mi, &ki);
        int ans = 0;
        for (int i = 0; i <= ki; i++) {
            int p = (pre[ni - i] - pre[ni - mi - i] + MOD) % MOD;
            int q = (suf[mi - i] - suf[mi - ki - i] + MOD) % MOD;
            int r = c[ni - mi][i] * fac[ki] % MOD * ifac[i] % MOD * ifac[ki - i] % MOD;
            ans = (ans + q * p % MOD * r % MOD) % MOD;
        }
        ans = ans * fac[ni] % MOD * ifac[ni - mi] % MOD * ifac[mi] % MOD * pow(ni - mi, l, MOD) % MOD;
        printf("%d\n", ans);
    }
    return 0;
}