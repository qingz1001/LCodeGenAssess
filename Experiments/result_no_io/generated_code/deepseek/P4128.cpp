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
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

void precompute_factorials(ll p) {
    factorial[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        factorial[i] = (factorial[i - 1] * i) % p;
    }
    inv_factorial[MAXN - 1] = mod_pow(factorial[MAXN - 1], p - 2, p);
    for (int i = MAXN - 2; i >= 0; i--) {
        inv_factorial[i] = (inv_factorial[i + 1] * (i + 1)) % p;
    }
}

ll binomial_coefficient(ll n, ll k, ll p) {
    if (k > n) return 0;
    return (factorial[n] * inv_factorial[k] % p) * inv_factorial[n - k] % p;
}

ll calculate_orbits(int n, int m, ll p) {
    ll result = 0;
    for (int k = 1; k <= n; k++) {
        result = (result + binomial_coefficient(n, k, p) * mod_pow(m, k * (n - k) + binomial_coefficient(k, 2, p), p) % p) % p;
    }
    return result;
}

int main() {
    int n, m;
    ll p;
    scanf("%d %d %lld", &n, &m, &p);

    precompute_factorials(p);

    ll result = calculate_orbits(n, m, p);
    printf("%lld\n", result);

    return 0;
}