#include <stdio.h>
#include <math.h>

int main() {
    double H, S1, V, L, K, n;
    scanf("%lf %lf %lf %lf %lf %lf", &H, &S1, &V, &L, &K, &n);

    int count = 0;

    for (double i = 0; i < n; i++) {
        double t = sqrt((2 * H + i * 0.5) / 5);
        double position = S1 + V * t - K * (i / n);
        if (fabs(position - L) <= 0.0001) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}