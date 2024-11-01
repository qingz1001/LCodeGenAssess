#include <stdio.h>

#define MOD 19940417

long long sum_of_mod(long long n, long long m) {
    long long sum = 0;
    for (long long i = 1; i <= n; i++) {
        sum = (sum + (n % i)) % MOD;
    }
    return sum;
}

long long solve(long long n, long long m) {
    long long total = (sum_of_mod(n, m) * sum_of_mod(m, n)) % MOD;
    long long common = 0;
    for (long long i = 1; i <= n && i <= m; i++) {
        common = (common + ((n % i) * (m % i)) % MOD) % MOD;
    }
    return (total - common + MOD) % MOD;
}

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    printf("%lld\n", solve(n, m));
    return 0;
}