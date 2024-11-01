#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

typedef long long ll;

ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    ll a[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    ll total_value = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                ll d_i = a[i];
                ll d_j = a[j];
                ll prod = (mod_pow(d_i, m, MOD) * mod_pow(d_j, m, MOD)) % MOD;
                ll sum = (mod_pow(d_i, m, MOD) + mod_pow(d_j, m, MOD)) % MOD;
                total_value = (total_value + prod * sum) % MOD;
            }
        }
    }

    printf("%lld\n", total_value);
    return 0;
}