#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numerator;
    int denominator;
} Fraction;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Fraction simplify(Fraction f) {
    int commonDivisor = gcd(abs(f.numerator), abs(f.denominator));
    f.numerator /= commonDivisor;
    f.denominator /= commonDivisor;
    if (f.denominator < 0) {
        f.numerator = -f.numerator;
        f.denominator = -f.denominator;
    }
    return f;
}

Fraction add(Fraction f1, Fraction f2) {
    Fraction result;
    result.numerator = f1.numerator * f2.denominator + f2.numerator * f1.denominator;
    result.denominator = f1.denominator * f2.denominator;
    return simplify(result);
}

Fraction subtract(Fraction f1, Fraction f2) {
    Fraction result;
    result.numerator = f1.numerator * f2.denominator - f2.numerator * f1.denominator;
    result.denominator = f1.denominator * f2.denominator;
    return simplify(result);
}

Fraction parseFraction(char *str) {
    Fraction f;
    char *slash = strchr(str, '/');
    if (slash == NULL) {
        f.numerator = atoi(str);
        f.denominator = 1;
    } else {
        *slash = '\0';
        f.numerator = atoi(str);
        f.denominator = atoi(slash + 1);
    }
    return f;
}

int main() {
    char expression[101];
    scanf("%s", expression);

    Fraction result = {0, 1};
    char *token = strtok(expression, "+-");
    int sign = 1;

    while (token != NULL) {
        Fraction current = parseFraction(token);
        if (sign == 1) {
            result = add(result, current);
        } else {
            result = subtract(result, current);
        }

        char *next = strtok(NULL, "+-");
        if (next != NULL) {
            if (*next == '+') {
                sign = 1;
            } else {
                sign = -1;
            }
            next++;
        }
        token = next;
    }

    if (result.denominator == 1) {
        printf("%d\n", result.numerator);
    } else {
        printf("%d/%d\n", result.numerator, result.denominator);
    }

    return 0;
}