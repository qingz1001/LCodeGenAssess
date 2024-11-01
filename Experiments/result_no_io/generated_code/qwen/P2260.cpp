#include <stdio.h>

#define MOD 19940417

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    long long sum = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i != j) {
                sum = (sum + ((long long)(n % i) * (m % j)) % MOD) % MOD;
            }
        }
    }

    printf("%lld\n", sum);

    return 0;
}