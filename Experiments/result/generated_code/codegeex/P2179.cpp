#include <stdio.h>
#include <math.h>

#define EPS 1e-8
#define INF 1e8

int n;
double EU;
double s[10005], k[10005], v[10005];

double f(double v, int i) {
    return k[i] * pow(v - v[i], 2);
}

double g(double v, int i) {
    return s[i] / (v - v[i]);
}

double calc(double E, int i) {
    double l = v[i], r = 100000, mid;
    while (r - l > EPS) {
        mid = (l + r) / 2;
        if (f(mid, i) * g(mid, i) > E) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return l;
}

int main() {
    scanf("%d %lf", &n, &EU);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf %lf", &s[i], &k[i], &v[i]);
    }

    double T = 0;
    for (int i = 1; i <= n; i++) {
        double v = calc(EU, i);
        T += s[i] / v;
        EU -= f(v, i) * g(v, i);
    }

    printf("%.6lf\n", T);
    return 0;
}