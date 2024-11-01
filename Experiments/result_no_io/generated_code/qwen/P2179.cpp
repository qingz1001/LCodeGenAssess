#include <stdio.h>
#include <math.h>

#define EPSILON 1e-6

int main() {
    int n;
    double EU;
    scanf("%d %lf", &n, &EU);

    double s[n], k[n], v_prime[n];
    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf %lf", &s[i], &k[i], &v_prime[i]);
    }

    double total_time = 0.0;
    for (int i = 0; i < n; ++i) {
        double v = sqrt(EU / (k[i] * s[i]));
        if (v_prime[i] > 0) {
            v += v_prime[i];
        } else {
            v -= v_prime[i];
        }
        total_time += s[i] / v;
    }

    printf("%.6f\n", total_time);
    return 0;
}