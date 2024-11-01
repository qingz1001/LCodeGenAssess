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

    int count = 0;
    int n = y0 / x0;

    for (int P = 1; P * P <= n; P++) {
        if (n % P == 0) {
            int Q = n / P;
            if (gcd(P, Q) == 1) {
                count += 2; // P, Q and Q, P
            }
        }
    }

    printf("%d\n", count);
    return 0;
}