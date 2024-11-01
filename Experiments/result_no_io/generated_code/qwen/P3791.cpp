#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int divisor_count(int num) {
    if (num == 0) return 0;
    int count = 0;
    for (int i = 1; i * i <= num; ++i) {
        if (num % i == 0) {
            if (i * i == num) count += 1;
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
            long long value = i ^ j ^ x;
            result = (result + divisor_count(value)) % MOD;
        }
    }

    printf("%lld\n", result);
    return 0;
}