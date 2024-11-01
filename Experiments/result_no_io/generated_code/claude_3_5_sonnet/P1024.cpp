#include <stdio.h>
#include <math.h>

double a, b, c, d;

double f(double x) {
    return a * x * x * x + b * x * x + c * x + d;
}

double find_root(double left, double right) {
    double mid;
    while (right - left > 1e-4) {
        mid = (left + right) / 2;
        if (f(left) * f(mid) <= 0) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left;
}

int main() {
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    
    double roots[3];
    int count = 0;
    
    for (double i = -100; i < 100 && count < 3; i++) {
        if (f(i) * f(i + 1) <= 0) {
            roots[count++] = find_root(i, i + 1);
        }
    }
    
    printf("%.2f %.2f %.2f\n", roots[0], roots[1], roots[2]);
    
    return 0;
}