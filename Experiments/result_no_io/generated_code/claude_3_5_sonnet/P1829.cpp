#include <stdio.h>

#define MOD 20101009

long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b % MOD;
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
    for (long long i = 1; i <= n; i++) {
        long long l = i, r = i;
        for (long long j = i; j <= m; j = r + 1) {
            r = m / (m / j);
            long long lcm_val = lcm(i, j);
            long long count = (r - l + 1) % MOD;
            sum = (sum + lcm_val * count) % MOD;
            l = r + 1;
        }
    }

    printf("%lld\n", sum);
    return 0;
}