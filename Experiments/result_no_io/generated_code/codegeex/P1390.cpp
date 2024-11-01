#include <stdio.h>

int main() {
    long long n, i, j, ans = 0;
    scanf("%lld", &n);

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            ans += __gcd(i, j);
        }
    }

    printf("%lld\n", ans);
    return 0;
}