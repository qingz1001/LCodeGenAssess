#include <stdio.h>

#define MOD 20101009

long long n, m, ans;
int prime[10000005], phi[10000005], tot;
bool vis[10000005];

void sieve(int maxn) {
    phi[1] = 1;
    for (int i = 2; i <= maxn; i++) {
        if (!vis[i]) {
            prime[++tot] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= tot && i * prime[j] <= maxn; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}

int main() {
    scanf("%lld%lld", &n, &m);
    if (n > m) {
        long long temp = n;
        n = m;
        m = temp;
    }
    sieve(n);
    for (int i = 1; i <= tot; i++) {
        for (long long j = 1; j * prime[i] <= n; j++) {
            long long max_factor = (n / j) / prime[i];
            long long min_factor = (m / j) / prime[i];
            ans = (ans + 1LL * phi[prime[i]] * (max_factor - min_factor + 1) % MOD * j % MOD * j % MOD) % MOD;
        }
    }
    printf("%lld\n", ans);
    return 0;
}