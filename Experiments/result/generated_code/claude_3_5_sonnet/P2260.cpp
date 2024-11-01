#include <stdio.h>

#define MOD 19940417

long long fast_pow(long long base, long long exp) {
    long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}

long long inv(long long x) {
    return fast_pow(x, MOD - 2);
}

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);

    if (n > m) {
        long long temp = n;
        n = m;
        m = temp;
    }

    long long sum = 0;
    long long s1 = 0, s2 = 0, s3 = 0;

    for (long long i = 1; i <= n; i++) {
        s1 = (s1 + n % i) % MOD;
        s2 = (s2 + m % i) % MOD;
        s3 = (s3 + (long long)(n / i) * (m / i) % MOD) % MOD;
    }

    sum = (s1 * s2 % MOD - s3 + MOD) % MOD;

    long long inv_2 = inv(2);
    long long result = (sum - ((n * m % MOD) * inv_2 % MOD) + MOD) % MOD;

    printf("%lld\n", result);

    return 0;
}