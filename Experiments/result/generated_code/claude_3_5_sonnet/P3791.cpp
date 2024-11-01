#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353
#define MAX_N 10000000

typedef long long ll;

ll d[MAX_N + 1];

void sieve() {
    for (int i = 1; i <= MAX_N; i++) {
        for (int j = i; j <= MAX_N; j += i) {
            d[j]++;
        }
    }
}

ll fast_pow(ll base, ll exp) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

ll solve(ll n, ll m, ll x) {
    ll result = 0;
    ll min_nm = (n < m) ? n : m;
    
    for (ll k = 0; k <= min_nm; k++) {
        ll cnt = ((n - k + 1) * (m - k + 1)) % MOD;
        ll val = k ^ x;
        if (val <= MAX_N) {
            result = (result + cnt * d[val]) % MOD;
        }
    }
    
    return result;
}

int main() {
    ll n, m, x;
    scanf("%lld %lld %lld", &n, &m, &x);
    
    sieve();
    
    ll ans = solve(n, m, x);
    printf("%lld\n", ans);
    
    return 0;
}