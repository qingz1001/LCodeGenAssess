#include <stdio.h>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void simplify(int *numerator, int *denominator) {
    int g = gcd(*numerator, *denominator);
    *numerator /= g;
    *denominator /= g;
}

void findPosition(int numerator, int denominator, int *row, int *col) {
    if (numerator == 1) {
        *row = 1;
        *col = denominator;
    } else if (denominator == 1) {
        *row = numerator;
        *col = 1;
    } else {
        *row = numerator;
        *col = denominator;
    }
}

int main() {
    int n1, d1, n2, d2;
    scanf("%d/%d", &n1, &d1);
    scanf("%d/%d", &n2, &d2);

    int resultNumerator = n1 * n2;
    int resultDenominator = d1 * d2;

    simplify(&resultNumerator, &resultDenominator);

    int row, col;
    findPosition(resultNumerator, resultDenominator, &row, &col);

    printf("%d %d\n", col, row);

    return 0;
}