#include <stdio.h>

#define MAX_M 5
#define MAX_P 100000

long long n, m, w[MAX_M];
long long p, mod_p[MAX_M];

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

long long modInverse(long long a, long long mod) {
    return power(a, mod - 2, mod);
}

long long comb(long long n, long long k, long long mod) {
    if (k > n) return 0;
    long long numerator = 1, denominator = 1;
    for (int i = 0; i < k; ++i) {
        numerator = (numerator * (n - i)) % mod;
        denominator = (denominator * (i + 1)) % mod;
    }
    return (numerator * modInverse(denominator, mod)) % mod;
}

int main() {
    scanf("%lld", &p);
    scanf("%lld %lld", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%lld", &w[i]);
    }

    // Check if the total number of gifts is enough
    long long total_gifts = 0;
    for (int i = 0; i < m; ++i) {
        total_gifts += w[i];
    }
    if (total_gifts > n) {
        printf("Impossible\n");
        return 0;
    }

    // Calculate the number of combinations modulo p
    long long result = 1;
    for (int i = 0; i < m; ++i) {
        result = (result * comb(n, w[i], p)) % p;
        n -= w[i];
    }

    printf("%lld\n", result);
    return 0;
}