#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000000000000000LL

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

long long mod_inv(long long x, long long mod) {
    return mod_pow(x, mod - 2, mod);
}

long long binomial_coefficient(long long n, long long k, long long mod) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    long long numerator = 1, denominator = 1;
    for (long long i = 0; i < k; i++) {
        numerator = (numerator * (n - i)) % mod;
        denominator = (denominator * (i + 1)) % mod;
    }
    return (numerator * mod_inv(denominator, mod)) % mod;
}

void print_last_k_digits(long long num, int k) {
    char buffer[20];
    sprintf(buffer, "%0*lld", k, num);
    printf("%s\n", buffer);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long a, b, k;
        scanf("%lld %lld %lld", &a, &b, &k);
        long long mod = 1;
        for (int i = 0; i < k; i++) {
            mod *= 10;
        }
        long long result = 0;
        for (long long i = 0; i <= a; i++) {
            for (long long j = 0; j <= b; j++) {
                if (i > j) {
                    result = (result + binomial_coefficient(a, i, mod) * binomial_coefficient(b, j, mod)) % mod;
                }
            }
        }
        print_last_k_digits(result, k);
    }
    return 0;
}