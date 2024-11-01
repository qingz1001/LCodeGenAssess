#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int x0, y0;
    scanf("%d %d", &x0, &y0);

    int count = 0;
    for (int i = 1; i * i <= y0; i++) {
        if (y0 % i == 0) {
            if (gcd(x0, i) == x0 && gcd(x0, y0 / i) == x0) {
                count++;
            }
            if (i != y0 / i && gcd(x0, y0 / i) == x0 && gcd(x0, i) == x0) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}