#include <stdio.h>
#include <string.h>

#define MOD 1000000000

long long power(long long base, long long exp, long long mod) {
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

long long binomial_coefficient(long long n, long long k, long long mod) {
    if (k > n - k) {
        k = n - k;
    }
    long long numerator = 1, denominator = 1;
    for (long long i = 0; i < k; i++) {
        numerator = (numerator * (n - i)) % mod;
        denominator = (denominator * (i + 1)) % mod;
    }
    return (numerator * power(denominator, mod - 2, mod)) % mod;
}

long long solve(long long a, long long b, int k) {
    long long mod = 1;
    for (int i = 0; i < k; i++) {
        mod *= 10;
    }

    long long total_ways = power(2, a, mod);
    long long invalid_ways = 0;

    for (long long i = 0; i <= b; i++) {
        invalid_ways = (invalid_ways + binomial_coefficient(a, i, mod)) % mod;
    }

    long long valid_ways = (total_ways - invalid_ways + mod) % mod;
    return valid_ways;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long a, b;
        int k;
        scanf("%lld %lld %d", &a, &b, &k);
        long long result = solve(a, b, k);
        printf("%0*lld\n", k, result);
    }
    return 0;
}