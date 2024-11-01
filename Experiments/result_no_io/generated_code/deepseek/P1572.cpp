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
    int common_divisor = gcd(abs(f.numerator), abs(f.denominator));
    f.numerator /= common_divisor;
    f.denominator /= common_divisor;
    if (f.denominator < 0) {
        f.numerator = -f.numerator;
        f.denominator = -f.denominator;
    }
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

        char *next_char = strtok(NULL, "+-");
        if (next_char != NULL) {
            if (*next_char == '-') {
                sign = -1;
                token = strtok(NULL, "+-");
            } else {
                sign = 1;
                token = next_char;
            }
        } else {
            break;
        }
    }

    if (result.denominator == 1) {
        printf("%d\n", result.numerator);
    } else {
        printf("%d/%d\n", result.numerator, result.denominator);
    }

    return 0;
}