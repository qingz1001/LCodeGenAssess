#include <stdio.h>
#include <math.h>

#define EPSILON 1e-9

double f(double x, double a, double b, double c) {
    return a * x * x + b * x + c;
}

double find_min_value(int n, double a[], double b[], double c[]) {
    double left = 0, right = 1000;
    while (right - left > EPSILON) {
        double mid1 = left + (right - left) / 3;
        double mid2 = right - (right - left) / 3;
        double max1 = -1e9, max2 = -1e9;
        for (int i = 0; i < n; i++) {
            max1 = f(mid1, a[i], b[i], c[i]) > max1 ? f(mid1, a[i], b[i], c[i]) : max1;
            max2 = f(mid2, a[i], b[i], c[i]) > max2 ? f(mid2, a[i], b[i], c[i]) : max2;
        }
        if (max1 > max2) {
            left = mid1;
        } else {
            right = mid2;
        }
    }
    return f((left + right) / 2, a[0], b[0], c[0]);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        double a[n], b[n], c[n];
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf %lf", &a[i], &b[i], &c[i]);
        }
        printf("%.4f\n", find_min_value(n, a, b, c));
    }
    return 0;
}