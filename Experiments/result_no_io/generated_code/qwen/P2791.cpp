#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

typedef long long ll;

ll power(ll base, ll exp) {
    ll result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

ll comb(int n, int k) {
    static ll fact[200001], inv_fact[200001];
    if (!fact[0]) {
        fact[0] = inv_fact[0] = 1;
        for (int i = 1; i <= 200000; ++i) {
            fact[i] = (fact[i - 1] * i) % MOD;
            inv_fact[i] = power(fact[i], MOD - 2);
        }
    }
    return (fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD) % MOD;
}

ll expected_failure(int n, int m, int k, int L) {
    ll total_ways = comb(n, k);
    ll success = 0;
    for (int x = 0; x <= k; ++x) {
        if (x <= m) {
            success = (success + comb(m, x) * comb(n - m, k - x)) % MOD;
        }
    }
    ll failure_rate = power(success, L);
    return (total_ways - failure_rate + MOD) % MOD;
}

int main() {
    int N, M, S, L;
    scanf("%d %d %d %d", &N, &M, &S, &L);

    for (int i = 0; i < S; ++i) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        printf("%lld\n", expected_failure(n, m, k, L));
    }

    return 0;
}