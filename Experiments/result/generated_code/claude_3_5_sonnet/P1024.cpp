#include <stdio.h>
#include <math.h>

#define EPSILON 1e-6

double f(double x, double a, double b, double c, double d) {
    return a * x * x * x + b * x * x + c * x + d;
}

double find_root(double left, double right, double a, double b, double c, double d) {
    double mid;
    while (right - left > EPSILON) {
        mid = (left + right) / 2;
        if (f(mid, a, b, c, d) * f(left, a, b, c, d) < 0) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left;
}

int main() {
    double a, b, c, d;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    double roots[3];
    int root_count = 0;

    for (int i = -100; i < 100; i++) {
        if (f(i, a, b, c, d) * f(i + 1, a, b, c, d) < 0) {
            roots[root_count++] = find_root(i, i + 1, a, b, c, d);
            if (root_count == 3) break;
        }
    }

    printf("%.2f %.2f %.2f\n", roots[0], roots[1], roots[2]);

    return 0;
}