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
    int g = gcd(abs(f.numerator), f.denominator);
    f.numerator /= g;
    f.denominator /= g;
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
    b.numerator = -b.numerator;
    return add(a, b);
}

int main() {
    char expression[101];
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = 0;

    Fraction result = {0, 1};
    Fraction current = {0, 1};
    char op = '+';
    int i = 0;

    while (expression[i] != '\0') {
        if (expression[i] == '+' || expression[i] == '-') {
            if (op == '+') result = add(result, current);
            else result = subtract(result, current);
            op = expression[i];
            current.numerator = 0;
            current.denominator = 1;
        } else if (expression[i] >= '0' && expression[i] <= '9') {
            int num = 0;
            while (expression[i] >= '0' && expression[i] <= '9') {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            if (current.denominator == 1) current.numerator = num;
            else current.denominator = num;
        } else if (expression[i] == '/') {
            current.denominator = 0;
        }
        i++;
    }

    if (op == '+') result = add(result, current);
    else result = subtract(result, current);

    result = simplify(result);
    if (result.denominator == 1) {
        printf("%d\n", result.numerator);
    } else {
        printf("%d/%d\n", result.numerator, result.denominator);
    }

    return 0;
}