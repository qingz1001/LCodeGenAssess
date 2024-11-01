#include <stdio.h>
#include <string.h>

#define MAXN 1000005

int n, p;
int prime[MAXN], cnt;
int vis[MAXN], mu[MAXN];
long long f[MAXN], g[MAXN];

void init() {
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}

long long qpow(long long a, int b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &p);
    init();
    
    for (int i = 1; i <= n; i++) {
        f[i] = qpow(2, n / i - 1);
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            g[i] = (g[i] + f[j] * mu[j / i]) % p;
        }
    }
    
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + g[i] * g[i]) % p;
    }
    
    printf("%lld\n", ans);
    return 0;
}