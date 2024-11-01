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

    long long expected_complexity = 0;
    for (int i = 1; i <= n; i++) {
        expected_complexity = (expected_complexity + mod_pow(m, MOD - 2, MOD)) % MOD;
    }

    printf("%lld\n", expected_complexity);
    return 0;
}