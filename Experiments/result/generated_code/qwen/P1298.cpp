#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void findClosestFraction(int M, int N, double R) {
    double closest_diff = 1e9;
    int closest_numerator = -1, closest_denominator = -1;

    for (int d = 1; d <= N; d++) {
        for (int n = 0; n <= M && (double)n / d <= R + closest_diff; n++) {
            if ((double)n / d == R) {
                int common_divisor = gcd(n, d);
                n /= common_divisor;
                d /= common_divisor;
                printf("%d/%d\n", n, d);
                return;
            } else if (fabs((double)n / d - R) < closest_diff) {
                closest_diff = fabs((double)n / d - R);
                closest_numerator = n;
                closest_denominator = d;
            }
        }
    }

    if (closest_numerator == -1 || closest_denominator == -1) {
        printf("TOO MANY\n");
    } else {
        int common_divisor = gcd(closest_numerator, closest_denominator);
        closest_numerator /= common_divisor;
        closest_denominator /= common_divisor;
        printf("%d/%d\n", closest_numerator, closest_denominator);
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