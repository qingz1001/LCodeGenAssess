#include <stdio.h>
#include <math.h>

int main() {
    double H, S1, V, L, K;
    int n;
    scanf("%lf %lf %lf %lf %lf %d", &H, &S1, &V, &L, &K, &n);

    int count = 0;
    for (int i = 0; i < n; i++) {
        double t = sqrt((2 * H) / 10);
        double x_ball = i + 0.5;
        double x_car = S1 - V * t;

        if (fabs(x_ball - x_car) <= 0.0001) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}