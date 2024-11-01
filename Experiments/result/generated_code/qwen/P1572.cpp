#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numerator;
    int denominator;
} Fraction;

void simplify(Fraction *f) {
    int gcd = f->numerator > f->denominator ? f->numerator : f->denominator;
    while (gcd != 0) {
        if (f->numerator % gcd == 0 && f->denominator % gcd == 0) {
            f->numerator /= gcd;
            f->denominator /= gcd;
            break;
        }
        gcd--;
    }
}

Fraction addFractions(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator + a.denominator * b.numerator;
    result.denominator = a.denominator * b.denominator;
    simplify(&result);
    return result;
}

Fraction subtractFractions(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator - a.denominator * b.numerator;
    result.denominator = a.denominator * b.denominator;
    simplify(&result);
    return result;
}

int main() {
    char expression[101];
    scanf("%s", expression);

    Fraction result = {0, 1};
    char *token = strtok(expression, "+-");
    Fraction current = {atoi(token), 1};

    token = strtok(NULL, "+-");
    while (token != NULL) {
        Fraction next;
        sscanf(token, "%d/%d", &next.numerator, &next.denominator);
        if (*expression == '-') {
            result = subtractFractions(result, next);
        } else {
            result = addFractions(result, next);
        }
        token = strtok(NULL, "+-");
    }

    printf("%d/%d\n", result.numerator, result.denominator);
    return 0;
}