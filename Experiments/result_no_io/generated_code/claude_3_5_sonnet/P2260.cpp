#include <stdio.h>

#define MOD 19940417

typedef long long ll;

ll fast_pow(ll base, ll exp) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

ll mod_inverse(ll x) {
    return fast_pow(x, MOD - 2);
}

ll sum_mod(ll n) {
    return ((n % MOD) * ((n + 1) % MOD) % MOD * mod_inverse(2)) % MOD;
}

ll calc(ll n, ll m) {
    ll result = 0;
    ll sum_n = sum_mod(n);
    ll sum_m = sum_mod(m);
    
    result = (sum_n * sum_m) % MOD;
    result = (result * 2) % MOD;
    
    ll sub = (((n % MOD) * (m % MOD)) % MOD * sum_mod(n < m ? n : m)) % MOD;
    
    result = (result - sub + MOD) % MOD;
    
    return result;
}

int main() {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    printf("%lld\n", calc(n, m));
    return 0;
}