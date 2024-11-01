#include <stdio.h>
#include <math.h>

#define EPS 1e-6
#define MAXN 10000

typedef struct {
    int a, b, c;
} Quadratic;

double f(Quadratic q, double x) {
    return q.a * x * x + q.b * x + q.c;
}

double max(double a, double b) {
    return a > b ? a : b;
}

double F(Quadratic qs[], int n, double x) {
    double max_val = -INFINITY;
    for (int i = 0; i < n; i++) {
        max_val = max(max_val, f(qs[i], x));
    }
    return max_val;
}

double ternary_search(Quadratic qs[], int n, double left, double right) {
    while (right - left > EPS) {
        double mid1 = left + (right - left) / 3;
        double mid2 = right - (right - left) / 3;
        if (F(qs, n, mid1) < F(qs, n, mid2)) {
            right = mid2;
        } else {
            left = mid1;
        }
    }
    return F(qs, n, left);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        Quadratic qs[MAXN];
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &qs[i].a, &qs[i].b, &qs[i].c);
        }
        double result = ternary_search(qs, n, 0, 1000);
        printf("%.4f\n", result);
    }
    return 0;
}