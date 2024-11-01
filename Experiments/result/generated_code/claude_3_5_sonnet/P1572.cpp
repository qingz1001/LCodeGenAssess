#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numerator;
    int denominator;
} Fraction;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

Fraction simplify(Fraction f) {
    int d = gcd(abs(f.numerator), f.denominator);
    f.numerator /= d;
    f.denominator /= d;
    return f;
}

Fraction add(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    result.denominator = a.denominator * b.denominator;
    return simplify(result);
}

Fraction subtract(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator - b.numerator * a.denominator;
    result.denominator = a.denominator * b.denominator;
    return simplify(result);
}

int main() {
    char expression[101];
    scanf("%100s", expression);

    Fraction result = {0, 1};
    char *token = strtok(expression, "+-");
    int sign = 1;

    while (token != NULL) {
        Fraction f;
        sscanf(token, "%d/%d", &f.numerator, &f.denominator);
        
        if (sign == 1) {
            result = add(result, f);
        } else {
            result = subtract(result, f);
        }

        token = strtok(NULL, "+-");
        if (token != NULL) {
            sign = (*(token - 1) == '+') ? 1 : -1;
        }
    }

    result = simplify(result);
    if (result.denominator == 1) {
        printf("%d\n", result.numerator);
    } else {
        printf("%d/%d\n", result.numerator, result.denominator);
    }

    return 0;
}