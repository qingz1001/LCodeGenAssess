#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 5
#define MAX_PRIMES 100

typedef long long ll;

ll P;
int n, m;
int w[MAX_M];
int primes[MAX_PRIMES], pcnt;
int factors[MAX_PRIMES], fcnt;

ll quick_pow(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

ll inv(ll x, ll p) {
    return quick_pow(x, p - 2, p);
}

ll comb(ll n, ll m, ll p) {
    if (m > n) return 0;
    ll res = 1;
    for (ll i = 1; i <= m; i++) {
        res = res * (n - i + 1) % p * inv(i, p) % p;
    }
    return res;
}

ll solve(ll mod) {
    ll res = 1;
    for (int i = 0; i < m; i++) {
        res = res * comb(n, w[i], mod) % mod;
        n -= w[i];
    }
    return res;
}

void factorize(ll x) {
    fcnt = 0;
    for (int i = 0; i < pcnt && primes[i] * primes[i] <= x; i++) {
        if (x % primes[i] == 0) {
            factors[fcnt++] = primes[i];
            while (x % primes[i] == 0) x /= primes[i];
        }
    }
    if (x > 1) factors[fcnt++] = x;
}

ll chinese_remainder(ll *a, ll *m, int n) {
    ll M = 1, res = 0;
    for (int i = 0; i < n; i++) M *= m[i];
    for (int i = 0; i < n; i++) {
        ll Mi = M / m[i];
        res = (res + a[i] * Mi % M * inv(Mi, m[i]) % M) % M;
    }
    return res;
}

int main() {
    scanf("%lld", &P);
    scanf("%d%d", &n, &m);
    
    int sum = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d", &w[i]);
        sum += w[i];
    }
    
    if (sum > n) {
        printf("Impossible\n");
        return 0;
    }
    
    for (int i = 2; i * i <= P; i++) {
        if (P % i == 0) {
            primes[pcnt++] = i;
            while (P % i == 0) P /= i;
        }
    }
    if (P > 1) primes[pcnt++] = P;
    
    factorize(P);
    
    ll a[MAX_PRIMES], mod[MAX_PRIMES];
    for (int i = 0; i < fcnt; i++) {
        mod[i] = factors[i];
        a[i] = solve(factors[i]);
    }
    
    printf("%lld\n", chinese_remainder(a, mod, fcnt));
    
    return 0;
}