#include <stdio.h>
#include <math.h>

double s[10005], k[10005], v[10005];
double E_U, T, L;

double f(double v) {
    double E = 0;
    for (int i = 1; i <= L; i++) {
        E += k[i] * (v - v[i]) * (v - v[i]) * s[i];
    }
    return E;
}

double solve(double l, double r) {
    double mid;
    while (r - l > 1e-10) {
        mid = (l + r) / 2;
        if (f(mid) <= E_U) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return r;
}

int main() {
    int n;
    scanf("%d%lf", &n, &E_U);
    L = n;
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf", &s[i], &k[i], &v[i]);
    }

    double t = 0;
    for (int i = 1; i <= n; i++) {
        double v0 = v[i] + sqrt(E_U / k[i] / s[i]);
        double v1 = solve(v[i], v0);
        t += s[i] / v1;
        E_U -= k[i] * (v1 - v[i]) * (v1 - v[i]) * s[i];
    }

    printf("%.6lf\n", t);
    return 0;
}