#include <stdio.h>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    int hypotenuse = a > b ? (a > c ? a : c) : (b > c ? b : c);
    int shorter_leg = a < b ? (a < c ? a : c) : (b < c ? b : c);

    int numerator = shorter_leg;
    int denominator = hypotenuse;

    int divisor = gcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;

    printf("%d/%d\n", numerator, denominator);

    return 0;
}