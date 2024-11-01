#include <stdio.h>
#include <stdlib.h>

#define MOD 998244353

int phi(int x) {
    int result = x;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0)
                x /= i;
            result -= result / i;
        }
    }
    if (x > 1)
        result -= result / x;
    return result;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        int n, m;
        scanf("%d %d", &n, &m);
        long long sum = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                sum += phi(i * j);
                sum %= MOD;
            }
        }
        printf("%lld\n", sum);
    }
    return 0;
}