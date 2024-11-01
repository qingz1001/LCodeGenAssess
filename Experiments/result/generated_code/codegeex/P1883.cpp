#include <stdio.h>
#include <math.h>

double f(double x, double a, double b, double c) {
    return a * x * x + b * x + c;
}

double findMin(double l, double r, double (*f)(double, double, double, double), double a, double b, double c) {
    while (r - l > 1e-10) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double fm1 = f(m1, a, b, c);
        double fm2 = f(m2, a, b, c);
        if (fm1 < fm2) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return f((l + r) / 2, a, b, c);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        double a, b, c;
        double minVal = 1e20;
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf%lf", &a, &b, &c);
            minVal = fmin(minVal, findMin(0, 1000, f, a, b, c));
        }
        printf("%.4lf\n", minVal);
    }
    return 0;
}