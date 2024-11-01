#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int x0, y0;
    scanf("%d %d", &x0, &y0);

    if (y0 % x0 != 0) {
        printf("0\n");
        return 0;
    }

    int factor = y0 / x0;
    int count = 0;

    for (int i = 1; i * i <= factor; i++) {
        if (factor % i == 0) {
            if (gcd(i, factor / i) == 1) {
                count += (i * i == factor) ? 1 : 2;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}