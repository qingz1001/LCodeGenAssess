#include <stdio.h>

#define MOD 19940417

int main() {
    long long n, m;
    scanf("%lld%lld", &n, &m);

    long long sum = 0;
    for (long long i = 1; i < n; i++) {
        for (long long j = 1; j < m; j++) {
            sum = (sum + (n % i) * (m % j)) % MOD;
        }
    }

    printf("%lld\n", sum);
    return 0;
}