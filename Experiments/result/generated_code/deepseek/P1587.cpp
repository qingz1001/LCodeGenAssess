#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int is_pure_cyclic(int x, int y, int k) {
    int g = gcd(x, y);
    x /= g;
    y /= g;
    while (gcd(y, k) != 1) {
        y /= gcd(y, k);
    }
    return y == 1;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int count = 0;
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            if (is_pure_cyclic(x, y, k)) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}