#include <stdio.h>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int x0, y0;
    scanf("%d %d", &x0, &y0);

    if (y0 % x0 != 0) {
        printf("0\n");
        return 0;
    }

    int n = y0 / x0;
    int count = 0;

    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (gcd(i, n / i) == 1) {
                count += (i * i == n) ? 1 : 2;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}