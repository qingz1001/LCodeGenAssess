#include <stdio.h>

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    long long ans = 0;
    for (int p = 1; p < k; p++) {
        int q = k - p;
        long long t = 0;
        for (int i = 1; i <= n; i++) {
            if (q % i == 0) {
                t += m / q * (n / i);
                if (m % q == i) t += m % q;
            }
        }
        if (q == 1) t++;
        ans += t * (k - 1);
    }

    printf("%lld\n", ans);
    return 0;
}