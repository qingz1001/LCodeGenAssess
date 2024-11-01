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

    if (gcd(x0, y0) != x0) {
        printf("0\n");
        return 0;
    }

    int count = 0;
    for (int i = 1; i * i <= y0; i++) {
        if (y0 % i == 0) {
            int j = y0 / i;
            if (j % x0 == 0 && gcd(i, j) == x0) {
                count += 2;
                if (i == j) count--;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}