#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void simplifyFraction(int *numerator, int *denominator) {
    int commonDivisor = gcd(*numerator, *denominator);
    *numerator /= commonDivisor;
    *denominator /= commonDivisor;
}

int main() {
    char expression[101];
    scanf("%s", expression);

    int numerator = 0, denominator = 1, sign = 1, currentNumerator = 0, currentDenominator = 1;

    for (int i = 0; i < strlen(expression); ++i) {
        if (expression[i] == '-') {
            sign = -1;
        } else if (expression[i] == '+') {
            sign = 1;
        } else if (expression[i] == '/') {
            currentDenominator = atoi(expression + i + 1);
            numerator += sign * currentNumerator * denominator / currentDenominator;
            denominator *= currentDenominator / gcd(currentDenominator, denominator);
            currentNumerator = 0;
            currentDenominator = 1;
        } else {
            currentNumerator = currentNumerator * 10 + (expression[i] - '0');
        }
    }

    numerator += sign * currentNumerator * denominator / currentDenominator;
    simplifyFraction(&numerator, &denominator);

    printf("%d/%d\n", numerator, denominator);

    return 0;
}