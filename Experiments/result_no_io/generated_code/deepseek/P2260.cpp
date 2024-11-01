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
    long long sum_n = sum_of_mod(n, m);
    long long sum_m = sum_of_mod(m, n);
    long long total = (sum_n * sum_m) % MOD;

    long long common_sum = 0;
    for (long long i = 1; i <= n && i <= m; i++) {
        common_sum = (common_sum + ((n % i) * (m % i)) % MOD) % MOD;
    }

    total = (total - common_sum + MOD) % MOD;
    return total;
}

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);
    printf("%lld\n", solve(n, m));
    return 0;
}