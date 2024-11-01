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

void reduceFraction(int *numerator, int *denominator) {
    int divisor = gcd(*numerator, *denominator);
    *numerator /= divisor;
    *denominator /= divisor;
}

int findPosition(int numerator, int denominator) {
    int n = 1;
    while (n * (n + 1) / 2 < numerator + denominator - 1) {
        n++;
    }
    int row = n - (numerator + denominator - n * (n + 1) / 2);
    int col = denominator - row;
    return row * 10000 + col;
}

int main() {
    int num1, den1, num2, den2;
    scanf("%d/%d", &num1, &den1);
    scanf("%d/%d", &num2, &den2);

    reduceFraction(&num1, &den1);
    reduceFraction(&num2, &den2);

    int productNumerator = num1 * num2;
    int productDenominator = den1 * den2;

    reduceFraction(&productNumerator, &productDenominator);

    printf("%d\n", findPosition(productNumerator, productDenominator));

    return 0;
}