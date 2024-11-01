#include <stdio.h>

#define MOD 20101009

long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b % MOD;
}

long long sum(long long n, long long m) {
    long long res = 0;
    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= m; j++) {
            res = (res + lcm(i, j)) % MOD;
        }
    }
    return res;
}

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    printf("%lld\n", sum(n, m));
    return 0;
}