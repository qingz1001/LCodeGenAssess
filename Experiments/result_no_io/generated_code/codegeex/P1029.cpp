#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int x0, y0;
    scanf("%d %d", &x0, &y0);

    int g = gcd(x0, y0);
    int P = x0 * y0 / g;

    if (g == x0 && P == y0) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}