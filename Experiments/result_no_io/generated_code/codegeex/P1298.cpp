#include <stdio.h>
#include <math.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int M, N;
    double R;
    scanf("%d %d", &M, &N);
    scanf("%lf", &R);

    int best_numerator = 0;
    int best_denominator = 1;
    double best_diff = fabs(R - best_numerator / (double)best_denominator);

    int too_many = 0;

    for (int denominator = 1; denominator <= N; ++denominator) {
        for (int numerator = 0; numerator <= M; ++numerator) {
            double diff = fabs(R - numerator / (double)denominator);
            if (diff < best_diff) {
                best_diff = diff;
                best_numerator = numerator;
                best_denominator = denominator;
                too_many = 0;
            } else if (diff == best_diff) {
                int gcd_value = gcd(best_numerator, best_denominator);
                int simplified_numerator = best_numerator / gcd_value;
                int simplified_denominator = best_denominator / gcd_value;
                int current_gcd_value = gcd(numerator, denominator);
                int current_simplified_numerator = numerator / current_gcd_value;
                int current_simplified_denominator = denominator / current_gcd_value;
                if (simplified_numerator * current_simplified_denominator != simplified_denominator * current_simplified_numerator) {
                    too_many = 1;
                }
            }
        }
    }

    if (too_many) {
        printf("TOO MANY\n");
    } else {
        int gcd_value = gcd(best_numerator, best_denominator);
        printf("%d/%d\n", best_numerator / gcd_value, best_denominator / gcd_value);
    }

    return 0;
}