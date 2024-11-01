#include <stdio.h>
#include <math.h>

#define MAXN 10000
#define EPS 1e-8

int n;
double E_U, s[MAXN], k[MAXN], v_prime[MAXN];

double calculate_time(double v[], int n) {
    double total_time = 0.0;
    for (int i = 0; i < n; i++) {
        total_time += s[i] / v[i];
    }
    return total_time;
}

double calculate_energy(double v[], int n) {
    double total_energy = 0.0;
    for (int i = 0; i < n; i++) {
        total_energy += k[i] * s[i] * (v[i] - v_prime[i]) * (v[i] - v_prime[i]);
    }
    return total_energy;
}

void binary_search(double v[], int n, double E_U) {
    double left = 0.0, right = 1e5;
    while (right - left > EPS) {
        double mid = (left + right) / 2.0;
        for (int i = 0; i < n; i++) {
            v[i] = mid;
        }
        if (calculate_energy(v, n) <= E_U) {
            left = mid;
        } else {
            right = mid;
        }
    }
    for (int i = 0; i < n; i++) {
        v[i] = left;
    }
}

int main() {
    scanf("%d %lf", &n, &E_U);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &s[i], &k[i], &v_prime[i]);
    }

    double v[MAXN];
    binary_search(v, n, E_U);

    double min_time = calculate_time(v, n);
    printf("%.6f\n", min_time);

    return 0;
}