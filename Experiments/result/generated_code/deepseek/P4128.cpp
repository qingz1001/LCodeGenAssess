#include <stdio.h>
#include <stdbool.h>

#define MAXN 54
#define MOD 1000000007

typedef long long ll;

ll factorial[MAXN];
ll inv_factorial[MAXN];

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

void precompute_factorials(int n, ll mod) {
    factorial[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorial[i] = (factorial[i - 1] * i) % mod;
    }
    inv_factorial[n] = mod_pow(factorial[n], mod - 2, mod);
    for (int i = n - 1; i >= 0; i--) {
        inv_factorial[i] = (inv_factorial[i + 1] * (i + 1)) % mod;
    }
}

ll binomial_coefficient(int n, int k, ll mod) {
    if (k > n || k < 0) return 0;
    return (factorial[n] * inv_factorial[k] % mod) * inv_factorial[n - k] % mod;
}

ll count_non_isomorphic_graphs(int n, int m, ll p) {
    precompute_factorials(n, p);
    ll result = 0;
    for (int k = 1; k <= n; k++) {
        ll term = binomial_coefficient(n, k, p) * mod_pow(m, k * (n - k) + k * (k - 1) / 2, p) % p;
        if (k % 2 == 1) {
            result = (result + term) % p;
        } else {
            result = (result - term + p) % p;
        }
    }
    return result;
}

int main() {
    int n, m;
    ll p;
    scanf("%d %d %lld", &n, &m, &p);
    printf("%lld\n", count_non_isomorphic_graphs(n, m, p));
    return 0;
}