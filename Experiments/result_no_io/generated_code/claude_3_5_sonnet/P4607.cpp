#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX_K 1000001

typedef long long ll;

ll powmod(ll base, ll exp, ll mod) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

ll solve(ll n, ll k, ll p) {
    ll total = powmod(k, n, p);
    ll bad = 0;

    if (n % 2 == 0) {
        bad = (bad + powmod(k, n / 2, p)) % p;
    } else {
        bad = (bad + powmod(k, (n + 1) / 2, p)) % p;
    }

    return (total - bad + p) % p;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        ll n, k, p;
        scanf("%lld %lld %lld", &n, &k, &p);
        printf("%lld\n", solve(n, k, p));
    }

    return 0;
}