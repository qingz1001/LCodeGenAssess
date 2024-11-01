#include <stdio.h>

#define MOD 19940417

long long n, m;

int main() {
    scanf("%lld%lld", &n, &m);
    long long ans = 0;

    for (long long i = 1; i < n; i++) {
        for (long long j = 1; j < m; j++) {
            ans = (ans + (n % i) * (m % j)) % MOD;
        }
    }

    printf("%lld\n", ans);
    return 0;
}