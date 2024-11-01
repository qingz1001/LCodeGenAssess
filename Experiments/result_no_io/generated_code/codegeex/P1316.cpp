#include <stdio.h>
#include <string.h>

#define MOD 1000000007

long long n, m;
long long fac[21], inv[21], powm[21];

long long power(long long base, long long exp) {
    long long result = 1;
    while (exp) {
        if (exp % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i <= 20; i++) {
        fac[i] = (fac[i-1] * i) % MOD;
    }
    inv[20] = power(fac[20], MOD-2);
    for (int i = 20; i >= 1; i--) {
        inv[i-1] = (inv[i] * i) % MOD;
    }
    powm[0] = 1;
    for (int i = 1; i <= 20; i++) {
        powm[i] = (powm[i-1] * m) % MOD;
    }
}

long long solve() {
    long long result = 0;
    for (int i = 1; i <= n; i++) {
        long long term = (fac[n] * inv[i] % MOD) * inv[n-i] % MOD;
        term = (term * powm[i]) % MOD;
        term = (term * (m - i + 1)) % MOD;
        result = (result + term) % MOD;
    }
    return result;
}

int main() {
    scanf("%lld %lld", &n, &m);
    init();
    long long answer = solve();
    printf("%lld\n", answer);
    return 0;
}