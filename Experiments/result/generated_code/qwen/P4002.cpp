#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

typedef long long ll;

int n, m;
ll a[30005];
ll fact[30005], inv_fact[30005];

void precompute_factorials() {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact[n] = pow(fact[n], MOD - 2);
    for (int i = n - 1; i >= 0; --i) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
}

ll mod_pow(ll base, ll exp) {
    if (exp == 0) return 1;
    ll half = mod_pow(base, exp / 2);
    ll result = half * half % MOD;
    if (exp % 2 == 1) result = result * base % MOD;
    return result;
}

ll comb(int n, int k) {
    if (k > n || k < 0) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }

    precompute_factorials();

    ll sum = 0, product = 1;
    for (int i = 0; i < n; ++i) {
        sum = (sum + a[i]) % MOD;
        product = product * mod_pow(a[i], m) % MOD;
    }

    ll result = (product * sum) % MOD;
    printf("%lld\n", result);

    return 0;
}