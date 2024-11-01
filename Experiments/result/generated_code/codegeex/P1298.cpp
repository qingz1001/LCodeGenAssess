#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int numerator;
    int denominator;
    double value;
} Fraction;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

Fraction findClosestFraction(int M, int N, double R) {
    Fraction closest = {0, 1, fabs(R)};
    int tooCloseCount = 0;

    for (int i = 0; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == 0 && j == 1) continue;
            double value = (double)i / j;
            double diff = fabs(value - R);
            if (diff < closest.value) {
                closest.numerator = i;
                closest.denominator = j;
                closest.value = diff;
                tooCloseCount = 0;
            } else if (diff == closest.value) {
                int gcdValue = gcd(closest.numerator, closest.denominator);
                int gcdCurr = gcd(i, j);
                if (closest.numerator / gcdValue == i / gcdCurr &&
                    closest.denominator / gcdValue == j / gcdCurr) {
                    tooCloseCount++;
                }
            }
        }
    }

    if (tooCloseCount > 0) {
        return (Fraction){-1, -1, 0}; // Indicate too many closest fractions
    }

    return closest;
}

int main() {
    int M, N;
    double R;
    scanf("%d %d", &M, &N);
    scanf("%lf", &R);

    Fraction closest = findClosestFraction(M, N, R);

    if (closest.numerator == -1) {
        printf("TOO MANY\n");
    } else {
        printf("%d/%d\n", closest.numerator, closest.denominator);
    }

    return 0;
}