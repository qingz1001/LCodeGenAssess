#include <stdio.h>

int main() {
    unsigned long long x, n, ans = 0;
    scanf("%llu%llu", &x, &n);
    while (n > 0) {
        if (n & 1) {
            ans += x;
        }
        x *= 2;
        n >>= 1;
    }
    printf("%llu\n", ans);
    return 0;
}