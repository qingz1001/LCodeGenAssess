#include <stdio.h>

#define MOD 19940417

int main() {
    long long n, m;
    scanf("%lld %lld", &n, &m);

    long long result = 0;

    for (long long i = 1; i <= n; ++i) {
        for (long long j = 1; j <= m; ++j) {
            if (i != j) {
                result = (result + ((n % i) * (m % j)) % MOD) % MOD;
            }
        }
    }

    printf("%lld\n", result);

    return 0;
}