#include <stdio.h>

#define MOD 20101009

long long n, m, ans;
long long phi[10000010], prime[10000010], p[10000010], mu[10000010];
int cnt;

void init() {
    phi[1] = 1;
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!p[i]) {
            prime[++cnt] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            p[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            mu[i * prime[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
    }
    for (int i = 1; i <= m; i++) {
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
    }
}

int main() {
    scanf("%lld%lld", &n, &m);
    if (n > m) {
        n ^= m;
        m ^= n;
        n ^= m;
    }
    init();
    for (long long i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        ans = (ans + (mu[j] - mu[i - 1]) * (n / i) % MOD * (phi[m / i] - phi[n / i]) % MOD) % MOD;
    }
    printf("%lld\n", (ans + MOD) % MOD);
    return 0;
}