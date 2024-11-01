#include <stdio.h>
#include <math.h>

#define MAX_N 10000
#define EPS 1e-6

double a[MAX_N], b[MAX_N], c[MAX_N];
int n;

double f(double x) {
    double max_val = -1e18;
    for (int i = 0; i < n; i++) {
        double val = a[i] * x * x + b[i] * x + c[i];
        if (val > max_val) max_val = val;
    }
    return max_val;
}

double ternary_search() {
    double l = 0, r = 1000;
    while (r - l > EPS) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        if (f(m1) > f(m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }
    return f(l);
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf %lf", &a[i], &b[i], &c[i]);
        }
        
        double result = ternary_search();
        printf("%.4f\n", result);
    }
    
    return 0;
}