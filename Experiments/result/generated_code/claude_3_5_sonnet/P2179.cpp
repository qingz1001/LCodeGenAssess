#include <stdio.h>
#include <math.h>

#define MAX_N 10000
#define EPS 1e-8

typedef struct {
    double s, k, v;
} Road;

Road roads[MAX_N];
int n;
double E_U;

double calculate_time(double E) {
    double total_time = 0;
    for (int i = 0; i < n; i++) {
        double a = roads[i].k * roads[i].s;
        double b = 2 * roads[i].k * roads[i].v * roads[i].s;
        double c = roads[i].k * roads[i].v * roads[i].v * roads[i].s - E;
        double delta = b * b - 4 * a * c;
        if (delta < 0) return 1e18;
        double v = (b + sqrt(delta)) / (2 * a);
        total_time += roads[i].s / v;
    }
    return total_time;
}

double binary_search(double left, double right) {
    while (right - left > EPS) {
        double mid = (left + right) / 2;
        if (calculate_time(mid) <= calculate_time(mid + EPS))
            right = mid;
        else
            left = mid;
    }
    return (left + right) / 2;
}

int main() {
    scanf("%d %lf", &n, &E_U);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &roads[i].s, &roads[i].k, &roads[i].v);
    }

    double E = binary_search(0, E_U);
    printf("%.6f\n", calculate_time(E));

    return 0;
}