#include <stdio.h>
#include <math.h>

#define MAX_N 10000
#define EPS 1e-7

typedef struct {
    double a, b, c;
} Function;

Function functions[MAX_N];
int n;

double evaluate(double x) {
    double max_val = -1e18;
    for (int i = 0; i < n; i++) {
        double val = functions[i].a * x * x + functions[i].b * x + functions[i].c;
        if (val > max_val) {
            max_val = val;
        }
    }
    return max_val;
}

double ternary_search() {
    double left = 0, right = 1000;
    while (right - left > EPS) {
        double m1 = left + (right - left) / 3;
        double m2 = right - (right - left) / 3;
        double f1 = evaluate(m1);
        double f2 = evaluate(m2);
        if (f1 < f2) {
            right = m2;
        } else {
            left = m1;
        }
    }
    return evaluate(left);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf %lf", &functions[i].a, &functions[i].b, &functions[i].c);
        }
        double result = ternary_search();
        printf("%.4f\n", result);
    }
    return 0;
}