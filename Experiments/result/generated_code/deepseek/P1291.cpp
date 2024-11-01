#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long numerator;
    long long denominator;
} Fraction;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Fraction simplify(Fraction f) {
    long long common_divisor = gcd(f.numerator, f.denominator);
    f.numerator /= common_divisor;
    f.denominator /= common_divisor;
    return f;
}

Fraction add(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator + b.numerator * a.denominator;
    result.denominator = a.denominator * b.denominator;
    return simplify(result);
}

Fraction multiply(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.numerator;
    result.denominator = a.denominator * b.denominator;
    return simplify(result);
}

Fraction divide(Fraction a, Fraction b) {
    Fraction result;
    result.numerator = a.numerator * b.denominator;
    result.denominator = a.denominator * b.numerator;
    return simplify(result);
}

void printFraction(Fraction f) {
    if (f.numerator % f.denominator == 0) {
        printf("%lld\n", f.numerator / f.denominator);
    } else {
        long long integer_part = f.numerator / f.denominator;
        long long fractional_numerator = f.numerator % f.denominator;
        if (integer_part != 0) {
            printf("%lld\n", fractional_numerator);
            printf("%lld", integer_part);
        } else {
            printf("%lld\n", fractional_numerator);
        }
        for (int i = 0; i < (int)log10(f.denominator) + 1; i++) {
            printf("-");
        }
        printf("\n");
        printf("%lld\n", f.denominator);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Fraction result = {0, 1};
    Fraction one = {1, 1};

    for (int i = 1; i <= n; i++) {
        Fraction term = {1, i};
        result = add(result, term);
    }

    result = multiply(result, (Fraction){n, 1});

    printFraction(result);

    return 0;
}