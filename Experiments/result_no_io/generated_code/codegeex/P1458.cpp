#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int n;
    scanf("%d", &n);

    for (int denominator = 1; denominator <= n; denominator++) {
        for (int numerator = 0; numerator < denominator; numerator++) {
            if (gcd(numerator, denominator) == 1) {
                printf("%d/%d\n", numerator, denominator);
            }
        }
    }

    return 0;
}