#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int n;
    scanf("%d", &n);

    long long numerator = 0, denominator = 1;
    for (int i = 1; i <= n; i++) {
        numerator = numerator * i + denominator * n;
        denominator *= i;
        long long g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;
    }

    if (numerator % denominator == 0) {
        printf("%lld\n", numerator / denominator);
    } else {
        long long integer_part = numerator / denominator;
        long long fractional_numerator = numerator % denominator;
        int denominator_digits = 0;
        long long temp = denominator;
        while (temp > 0) {
            denominator_digits++;
            temp /= 10;
        }

        printf("%lld\n", fractional_numerator);
        if (integer_part > 0) {
            printf("%lld", integer_part);
        }
        for (int i = 0; i < denominator_digits; i++) {
            printf("-");
        }
        printf("\n");
        printf("%lld\n", denominator);
    }

    return 0;
}