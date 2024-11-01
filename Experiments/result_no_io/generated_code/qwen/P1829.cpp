#include <stdio.h>

#define MOD 20101009

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);

    long long sum = 0;
    for (long long i = 1; i <= n; ++i) {
        for (long long j = 1; j <= m; ++j) {
            long long lcm = (i * j) / __gcd(i, j);
            sum = (sum + lcm) % MOD;
        }
    }

    printf("%lld\n", sum);
    return 0;
}