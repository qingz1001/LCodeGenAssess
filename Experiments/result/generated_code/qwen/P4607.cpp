#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

long long power(long long base, long long exp) {
    if (exp == 0) return 1;
    long long result = power(base, exp / 2);
    result = (result * result) % MOD;
    if (exp % 2 != 0) result = (result * base) % MOD;
    return result;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n, k, p;
        scanf("%lld %lld %lld", &n, &k, &p);

        long long total_strings = power(k, n);
        long long palindromic_strings = 0;

        for (long long len = 1; len <= n; ++len) {
            palindromic_strings += power(k, len / 2);
            palindromic_strings %= MOD;
        }

        long long bad_strings = (total_strings - palindromic_strings + MOD) % MOD;
        printf("%lld\n", bad_strings);
    }
    return 0;
}