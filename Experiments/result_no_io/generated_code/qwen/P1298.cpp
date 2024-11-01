#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void findClosestFraction(int M, int N, double R) {
    int best_numerator = -1, best_denominator = -1;
    double best_error = 1.0;

    for (int denominator = 1; denominator <= N; ++denominator) {
        for (int numerator = 0; numerator <= M && numerator <= denominator * R; ++numerator) {
            if (numerator == 0 || denominator == 0) continue;
            int common_divisor = gcd(numerator, denominator);
            numerator /= common_divisor;
            denominator /= common_divisor;
            double current_value = (double)numerator / denominator;
            double error = fabs(current_value - R);

            if (error < best_error) {
                best_error = error;
                best_numerator = numerator;
                best_denominator = denominator;
            } else if (error == best_error) {
                printf("TOO MANY\n");
                return;
            }
        }
    }

    if (best_numerator == -1 && best_denominator == -1) {
        printf("TOO MANY\n");
    } else {
        printf("%d/%d\n", best_numerator, best_denominator);
    }
}

int main() {
    int M, N;
    double R;
    scanf("%d %d", &M, &N);
    scanf("%lf", &R);
    findClosestFraction(M, N, R);
    return 0;
}