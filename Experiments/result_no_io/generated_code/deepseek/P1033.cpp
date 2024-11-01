#include <stdio.h>
#include <math.h>

int main() {
    double H, S1, V, L, K;
    int n;
    scanf("%lf %lf %lf %lf %lf %d", &H, &S1, &V, &L, &K, &n);

    double g = 10.0;
    double t_max = sqrt(2 * (H - K) / g);
    double t_min = sqrt(2 * H / g);

    double x_max = S1 + L - V * t_min;
    double x_min = S1 - V * t_max;

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (i >= x_min - 0.0001 && i <= x_max + 0.0001) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}