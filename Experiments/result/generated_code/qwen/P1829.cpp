#include <stdio.h>

#define MOD 20101009

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    long long sum = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            sum += (long long)i * j / __gcd(i, j);
            sum %= MOD;
        }
    }

    printf("%lld\n", sum);

    return 0;
}