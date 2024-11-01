#include <stdio.h>
#include <math.h>

#define EPS 0.0001
#define G 10.0

int main() {
    double H, S1, V, L, K;
    int n;
    scanf("%lf %lf %lf %lf %lf %d", &H, &S1, &V, &L, &K, &n);

    int count = 0;
    double t_max = sqrt((H - K) / (0.5 * G));
    double t_min = sqrt(H / (0.5 * G));

    double s_max = S1 + L - V * t_min;
    double s_min = S1 - V * t_max;

    for (int i = 0; i < n; i++) {
        if (i >= s_min - EPS && i <= s_max + EPS) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}