#include <stdio.h>
#include <math.h>

#define MAXN 10000
#define EPS 1e-12

int n;
double E_U, s[MAXN], k[MAXN], v_prime[MAXN];

double calculate_time(double v[], int n) {
    double total_time = 0;
    for (int i = 0; i < n; i++) {
        total_time += s[i] / v[i];
    }
    return total_time;
}

double calculate_energy(double v[], int n) {
    double total_energy = 0;
    for (int i = 0; i < n; i++) {
        total_energy += k[i] * s[i] * (v[i] - v_prime[i]) * (v[i] - v_prime[i]);
    }
    return total_energy;
}

double binary_search(double left, double right, double target_energy) {
    double mid;
    double v[MAXN];
    while (right - left > EPS) {
        mid = (left + right) / 2;
        for (int i = 0; i < n; i++) {
            v[i] = sqrt(target_energy / (k[i] * s[i])) + v_prime[i];
        }
        double energy = calculate_energy(v, n);
        if (energy < target_energy) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return mid;
}

int main() {
    scanf("%d %lf", &n, &E_U);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &s[i], &k[i], &v_prime[i]);
    }

    double left = 0, right = 1e5;
    double target_energy = E_U;
    double optimal_speed = binary_search(left, right, target_energy);

    double v[MAXN];
    for (int i = 0; i < n; i++) {
        v[i] = sqrt(target_energy / (k[i] * s[i])) + v_prime[i];
    }

    double total_time = calculate_time(v, n);
    printf("%.12lf\n", total_time);

    return 0;
}