#include <stdio.h>
#include <stdlib.h>

void print_fraction(int numerator, int denominator) {
    if (numerator == 0) {
        printf("0\n");
        return;
    }
    int gcd = numerator > denominator ? gcd(numerator, denominator) : gcd(denominator, numerator);
    numerator /= gcd;
    denominator /= gcd;

    if (denominator == 1) {
        printf("%d\n", numerator);
    } else {
        int whole_part = numerator / denominator;
        numerator %= denominator;
        int leading_spaces = 1 + (whole_part != 0);
        for (int i = 0; i < leading_spaces; i++) {
            printf(" ");
        }
        printf("%d\n", numerator);
        for (int i = 0; i < leading_spaces; i++) {
            printf("-");
        }
        printf("\n");
        printf("%d\n", denominator);
    }
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int n;
    scanf("%d", &n);

    int numerator = 0;
    int denominator = 1;

    for (int i = 1; i <= n; i++) {
        numerator += denominator * (i - 1);
        denominator *= i;
    }

    print_fraction(numerator, denominator);

    return 0;
}