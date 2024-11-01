#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MOD 20101009
#define MAXN 10000000

typedef long long ll;

ll sum[MAXN + 1], mu[MAXN + 1], prime[MAXN + 1], cnt;
bool vis[MAXN + 1];

void init() {
    mu[1] = 1;
    for (int i = 2; i <= MAXN; ++i) {
        if (!vis[i]) {
            prime[cnt++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < cnt && i * prime[j] <= MAXN; ++j) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
    for (int i = 1; i <= MAXN; ++i) {
        sum[i] = (sum[i - 1] + (ll)i * i % MOD * (mu[i] + MOD)) % MOD;
    }
}

ll S(ll x) {
    return x * (x + 1) / 2 % MOD;
}

ll f(ll n, ll m) {
    ll res = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        r = (n / (n / l) < m / (m / l)) ? n / (n / l) : m / (m / l);
        res = (res + (sum[r] - sum[l - 1] + MOD) % MOD * S(n / l) % MOD * S(m / l) % MOD) % MOD;
    }
    return res;
}

int main() {
    init();
    ll n, m;
    scanf("%lld %lld", &n, &m);
    if (n > m) {
        ll temp = n;
        n = m;
        m = temp;
    }
    ll ans = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        r = (n / (n / l) < m / (m / l)) ? n / (n / l) : m / (m / l);
        ans = (ans + (l + r) * (r - l + 1) / 2 % MOD * f(n / l, m / l) % MOD) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}