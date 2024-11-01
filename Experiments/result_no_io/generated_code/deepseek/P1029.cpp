#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
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
            int p = i * x0;
            int q = (n / i) * x0;
            if (gcd(p, q) == x0 && (p * q) / gcd(p, q) == y0) {
                if (p != q) {
                    count += 2; // (p, q) and (q, p)
                } else {
                    count += 1; // (p, p)
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}