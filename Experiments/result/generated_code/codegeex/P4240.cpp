#include <stdio.h>
#define MAXN 100000
#define MOD 998244353

int T, n, m;
int phi[MAXN + 1], prime[MAXN + 1], mu[MAXN + 1];
int cnt, vis[MAXN + 1];

void init() {
    phi[1] = mu[1] = 1;
    for (int i = 2; i <= MAXN; i++) {
        if (!vis[i]) {
            prime[cnt++] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (int j = 0; j < cnt && i * prime[j] <= MAXN; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
}

int main() {
    init();
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        if (n > m) {
            n ^= m;
            m ^= n;
            n ^= m;
        }
        int ans = 0;
        for (int i = 1, j; i <= n; i = j + 1) {
            j = n / (n / i);
            int lcm = (long long)(n / i) * m % MOD;
            ans = (ans + (long long)(mu[j] - mu[i - 1]) * phi[lcm] % MOD) % MOD;
        }
        printf("%d\n", (ans + MOD) % MOD);
    }
    return 0;
}