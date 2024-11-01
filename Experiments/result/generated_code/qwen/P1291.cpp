#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void print_fraction(int numerator, int denominator) {
    if (denominator == 1) {
        printf("%d\n", numerator);
    } else {
        int common_divisor = gcd(numerator, denominator);
        numerator /= common_divisor;
        denominator /= common_divisor;
        printf("%d\n%d--\n%*d\n", numerator, denominator, (int)log10(denominator), denominator);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int numerator = 1;
    int denominator = 1;

    for (int i = 1; i <= n; i++) {
        numerator *= i + 1;
        denominator *= i;
    }

    print_fraction(numerator, denominator);

    return 0;
}