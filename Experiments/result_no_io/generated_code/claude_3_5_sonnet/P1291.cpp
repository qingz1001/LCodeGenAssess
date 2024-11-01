#include <stdio.h>
#include <math.h>

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int n;
    scanf("%d", &n);

    long long numerator = 0;
    long long denominator = 1;

    for (int i = 1; i <= n; i++) {
        numerator = numerator * i + denominator * n;
        denominator *= i;
    }

    long long g = gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;

    long long integral = numerator / denominator;
    numerator %= denominator;

    if (numerator == 0) {
        printf("%lld\n", integral);
    } else {
        int digits = (int)log10(denominator) + 1;
        if (integral > 0) {
            printf(" %lld\n%lld", numerator, integral);
            for (int i = 0; i < digits; i++) printf("-");
            printf("\n %lld\n", denominator);
        } else {
            printf(" %lld\n", numerator);
            for (int i = 0; i < digits; i++) printf("-");
            printf("\n %lld\n", denominator);
        }
    }

    return 0;
}