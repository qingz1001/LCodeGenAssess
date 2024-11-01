#include <stdio.h>

#define MAXN 1000000000
#define MAXK 2000

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (gcd(i, j) != 1) continue;

            int r = 1, l = 1;
            while (r * i % j != 0) {
                r = r * k % j;
                l++;
            }

            if (l % 2 == 0) {
                ans += (n / j) * (m / i);
            } else {
                ans += ((n / j) + 1) * ((m / i) + 1) - 2;
            }
        }
    }

    printf("%lld\n", ans);
    return 0;
}