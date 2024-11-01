#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MOD 998244353

int phi[MAXN], mu[MAXN], prime[MAXN], sum[MAXN];
int vis[MAXN], cnt, T, n, m;

void getphi(int n) {
    phi[1] = mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + mu[i];
    }
}

int main() {
    scanf("%d", &T);
    getphi(MAXN - 1);
    while (T--) {
        scanf("%d%d", &n, &m);
        if (n > m) {
            n ^= m ^= n ^= m;
        }
        int ans = 0;
        for (int l = 1, r; l <= n; l = r + 1) {
            r = n / (n / l);
            ans = (ans + 1LL * (sum[r] - sum[l - 1]) * (n / l) % MOD * (m / l) % MOD) % MOD;
        }
        printf("%d\n", ans);
    }
    return 0;
}