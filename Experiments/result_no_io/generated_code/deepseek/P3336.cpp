#include <stdio.h>
#include <stdlib.h>

#define MOD 19940417

typedef long long ll;

ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    ll N, K;
    scanf("%lld %lld", &N, &K);

    ll *x = (ll *)malloc(K * sizeof(ll));
    ll *f = (ll *)malloc(K * sizeof(ll));

    for (ll i = 0; i < K; i++) {
        scanf("%lld %lld", &x[i], &f[i]);
    }

    // 计算满足条件的函数数量
    ll count = 1;
    for (ll i = 0; i < K - 1; i++) {
        ll dx = x[i + 1] - x[i];
        ll df = abs(f[i + 1] - f[i]);
        if (df > dx) {
            count = 0;
            break;
        }
        count = (count * (dx - df + 1)) % MOD;
    }

    // 计算最大值
    ll max_value = 0;
    for (ll i = 0; i < K; i++) {
        max_value = (max_value > f[i]) ? max_value : f[i];
    }

    printf("%lld %lld\n", count, max_value);

    free(x);
    free(f);

    return 0;
}