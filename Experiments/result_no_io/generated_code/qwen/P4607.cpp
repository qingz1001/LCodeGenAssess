#include <stdio.h>
#include <math.h>

#define MOD 1000000007

long long power(long long base, long long exp) {
    if (exp == 0) return 1;
    long long half = power(base, exp / 2);
    long long result = (half * half) % MOD;
    if (exp % 2 != 0) result = (result * base) % MOD;
    return result;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        long long n, k, p;
        scanf("%lld %lld %lld", &n, &k, &p);

        // Total number of strings of length n with k characters
        long long total_strings = power(k, n);

        // Number of palindromic strings of length n with k characters
        long long palindromic_strings = 0;
        for (long long len = 1; len <= n; len++) {
            if (len == 1) {
                palindromic_strings += k;
            } else if (len % 2 == 1) {
                long long mid = len / 2 + 1;
                palindromic_strings = (palindromic_strings + power(k, mid)) % MOD;
            } else {
                long long left = len / 2;
                palindromic_strings = (palindromic_strings + power(k, left)) % MOD;
            }
        }

        // Number of strings that become palindromic after removing a prefix and appending it to the end
        long long invalid_strings = (total_strings - palindromic_strings + MOD) % MOD;

        printf("%lld\n", invalid_strings);
    }
    return 0;
}