#include <stdio.h>
#define MOD 998244353

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int divisor_count(int x) {
    if (x == 0) return 0;
    int count = 0;
    for (int i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            if (i * i == x) count += 1;
            else count += 2;
        }
    }
    return count;
}

int main() {
    long long n, m, x;
    scanf("%lld %lld %lld", &n, &m, &x);

    long long result = 0;
    for (long long i = 0; i <= n; ++i) {
        for (long long j = 0; j <= m; ++j) {
            long long val = i ^ j ^ x;
            result = (result + divisor_count(val)) % MOD;
        }
    }

    printf("%lld\n", result);
    return 0;
}