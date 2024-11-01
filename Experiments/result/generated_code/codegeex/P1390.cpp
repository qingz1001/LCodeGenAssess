#include <stdio.h>

int main() {
    int n, i, j, ans = 0;
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        for (j = i + 1; j <= n; j++) {
            ans += __gcd(i, j);
        }
    }

    printf("%d\n", ans);
    return 0;
}