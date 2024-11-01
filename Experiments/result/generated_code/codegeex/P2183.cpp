#include <stdio.h>

#define MAX_P 100000

long long n, m, w[6], p, mod, primes[MAX_P], prime_count, fac[MAX_P], inv[MAX_P];

void sieve(long long max_prime) {
    for (long long i = 2; i <= max_prime; ++i) {
        if (!primes[i]) {
            primes[++prime_count] = i;
            fac[prime_count] = i;
            inv[prime_count] = 1;
            for (long long j = 2 * i; j <= max_prime; j += i) {
                primes[j] = 1;
            }
        }
        if (i > 200) {
            fac[prime_count] *= i;
            inv[prime_count] = (mod - mod / i) * inv[mod % i] % mod;
            if (fac[prime_count] >= mod) {
                fac[prime_count] %= mod;
                inv[prime_count] %= mod;
            }
        }
    }
}

long long mod_factorial(long long x) {
    if (x == 0 || x == 1) return 1;
    long long result = 1;
    for (long long i = 1; i <= prime_count; ++i) {
        long long count = 0;
        long long num = x;
        while (num > 0) {
            num /= primes[i];
            count += num;
        }
        result = result * fac[i] % mod;
        for (long long j = 1; j <= count; ++j) {
            result = result * inv[i] % mod;
        }
    }
    return result;
}

int main() {
    scanf("%lld", &mod);
    scanf("%lld%lld", &n, &m);
    sieve(200);
    for (long long i = 0; i < m; ++i) {
        scanf("%lld", &w[i]);
    }

    long long sum = 0;
    for (long long i = 0; i < m; ++i) {
        sum += w[i];
    }

    if (sum > n) {
        printf("Impossible\n");
        return 0;
    }

    long long result = 1;
    for (long long i = 0; i < m; ++i) {
        result = result * mod_factorial(n - sum + i) % mod;
        result = result * mod_factorial(w[i]) % mod;
        n -= w[i];
    }

    printf("%lld\n", result);
    return 0;
}