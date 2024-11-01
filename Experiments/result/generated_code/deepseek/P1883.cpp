#include <stdio.h>
#include <math.h>

#define MAXN 10000
#define EPS 1e-9

typedef struct {
    int a, b, c;
} Quadratic;

double evaluate(Quadratic q, double x) {
    return q.a * x * x + q.b * x + q.c;
}

double max_of_functions(Quadratic functions[], int n, double x) {
    double max_val = evaluate(functions[0], x);
    for (int i = 1; i < n; i++) {
        double val = evaluate(functions[i], x);
        if (val > max_val) {
            max_val = val;
        }
    }
    return max_val;
}

double ternary_search(Quadratic functions[], int n, double left, double right) {
    while (right - left > EPS) {
        double mid1 = left + (right - left) / 3;
        double mid2 = right - (right - left) / 3;
        double f_mid1 = max_of_functions(functions, n, mid1);
        double f_mid2 = max_of_functions(functions, n, mid2);
        if (f_mid1 < f_mid2) {
            right = mid2;
        } else {
            left = mid1;
        }
    }
    return max_of_functions(functions, n, (left + right) / 2);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        Quadratic functions[MAXN];
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &functions[i].a, &functions[i].b, &functions[i].c);
        }
        double result = ternary_search(functions, n, 0, 1000);
        printf("%.4f\n", result);
    }
    return 0;
}