#include <stdio.h>
#include <math.h>

int main() {
    double H, S1, V, L, K, n;
    scanf("%lf %lf %lf %lf %lf %lf", &H, &S1, &V, &L, &K, &n);

    int count = 0;
    double g = 10.0;

    for (int i = 0; i < n; i++) {
        double t = sqrt(2 * H / g);
        double distance = S1 + V * t - i;

        if (distance <= 0.0001 || (distance + L >= 0 && distance <= L)) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}