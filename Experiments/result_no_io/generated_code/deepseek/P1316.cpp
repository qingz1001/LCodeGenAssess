#include <stdio.h>

#define MOD 1000000007

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    long long numerator = 0;
    for (int k = 1; k <= n; k++) {
        numerator = (numerator + (mod_pow(m, k, MOD) * k % MOD)) % MOD;
    }

    long long denominator = mod_pow(m, n, MOD);
    long long inverse_denominator = mod_pow(denominator, MOD - 2, MOD);

    long long result = (numerator * inverse_denominator) % MOD;
    printf("%lld\n", result);

    return 0;
}