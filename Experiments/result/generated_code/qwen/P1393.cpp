#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

typedef long long ll;

ll modpow(ll base, ll exp) {
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

int main() {
    int n, m, s_len;
    scanf("%d %d %d", &n, &m, &s_len);
    
    ll total = modpow(m, n);
    ll valid = 0;
    
    for (int i = 0; i <= n - s_len; ++i) {
        ll count = modpow(m - s_len + 1, n - i - s_len);
        valid = (valid + count) % MOD;
    }
    
    ll probability = (valid * modpow(total, MOD - 2)) % MOD;
    printf("%lld\n", probability);
    
    return 0;
}