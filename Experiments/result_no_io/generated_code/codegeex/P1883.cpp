#include <stdio.h>
#include <math.h>

#define EPSILON 1e-6

typedef struct {
    double a, b, c;
} QuadraticFunction;

double f(QuadraticFunction f, double x) {
    return f.a * x * x + f.b * x + f.c;
}

double ternarySearch(QuadraticFunction f1, QuadraticFunction f2, double l, double r) {
    while (r - l > EPSILON) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double fm1 = f(f1, m1);
        double fm2 = f(f2, m2);
        if (fm1 < fm2) {
            r = m2;
        } else {
            l = m1;
        }
    }
    return l;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        QuadraticFunction functions[n];
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf %lf", &functions[i].a, &functions[i].b, &functions[i].c);
        }

        double min_value = INFINITY;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                double x = ternarySearch(functions[i], functions[j], 0, 1000);
                double value = f(functions[i], x);
                if (f(functions[j], x) > value) {
                    value = f(functions[j], x);
                }
                if (value < min_value) {
                    min_value = value;
                }
            }
        }

        printf("%.4lf\n", min_value);
    }
    return 0;
}