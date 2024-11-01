#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAX_A 10000001

typedef long long ll;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll pow_mod(ll base, ll exp, ll mod) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

ll inv(ll x) {
    return pow_mod(x, MOD - 2, MOD);
}

int main() {
    static int is_prime[MAX_A];
    static ll f[MAX_A], g[MAX_A];
    
    memset(is_prime, 1, sizeof(is_prime));
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i < MAX_A; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAX_A; j += i) {
                is_prime[j] = 0;
            }
        }
    }
    
    for (int i = 1; i < MAX_A; i++) {
        f[i] = i;
        g[i] = 1;
    }
    
    for (int i = 2; i < MAX_A; i++) {
        if (is_prime[i]) {
            for (int j = i; j < MAX_A; j += i) {
                int cnt = 0;
                while (f[j] % i == 0) {
                    f[j] /= i;
                    cnt++;
                }
                g[j] *= cnt + 1;
            }
        }
    }
    
    int T;
    scanf("%d", &T);
    
    while (T--) {
        ll n, a;
        scanf("%lld %lld", &n, &a);
        
        ll ans = 0;
        for (int i = 1; i <= a; i++) {
            ll tmp = pow_mod(g[i], n, MOD);
            if (n % 2 == 0) {
                tmp = (tmp + pow_mod(g[i], n / 2, MOD) * f[i] % MOD) % MOD;
            }
            ans = (ans + tmp) % MOD;
        }
        
        ans = ans * inv(2 * n) % MOD;
        printf("%lld\n", ans);
    }
    
    return 0;
}