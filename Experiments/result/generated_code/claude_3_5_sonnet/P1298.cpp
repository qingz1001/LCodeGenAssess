#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int M, N;
    double R;
    scanf("%d %d", &M, &N);
    scanf("%lf", &R);

    int best_num = 0, best_den = 1;
    double min_diff = R;
    int count = 0;

    for (int den = 1; den <= N; den++) {
        int num = (int)(R * den + 0.5);
        if (num > M) num = M;

        while (num >= 0 && (double)num / den <= R) {
            double diff = fabs(R - (double)num / den);
            if (diff < min_diff - EPSILON) {
                min_diff = diff;
                best_num = num;
                best_den = den;
                count = 1;
            } else if (fabs(diff - min_diff) < EPSILON) {
                count++;
            }
            num--;
        }
    }

    if (count > 1) {
        printf("TOO MANY\n");
    } else {
        int g = gcd(best_num, best_den);
        printf("%d/%d\n", best_num / g, best_den / g);
    }

    return 0;
}