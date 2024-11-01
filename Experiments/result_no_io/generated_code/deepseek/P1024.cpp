#include <stdio.h>
#include <math.h>

double a, b, c, d;

double f(double x) {
    return a * x * x * x + b * x * x + c * x + d;
}

double findRoot(double left, double right) {
    while (right - left > 1e-5) {
        double mid = (left + right) / 2;
        if (f(mid) * f(left) <= 0) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return (left + right) / 2;
}

int main() {
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

    double roots[3];
    int count = 0;

    for (double x = -100; x <= 100; x += 1) {
        if (f(x) == 0) {
            roots[count++] = x;
        } else if (f(x) * f(x + 1) < 0) {
            roots[count++] = findRoot(x, x + 1);
        }
        if (count == 3) break;
    }

    printf("%.2f %.2f %.2f\n", roots[0], roots[1], roots[2]);

    return 0;
}