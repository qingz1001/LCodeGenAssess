#include <stdio.h>
#include <math.h>

#define MAXN 10005
#define EPS 1e-8

double s[MAXN], k[MAXN], v[MAXN];
int n;
double E;

double f(double T) {
    double energy = 0;
    for (int i = 0; i < n; i++) {
        double x = s[i] / T;
        energy += k[i] * (x - v[i]) * (x - v[i]) * s[i];
    }
    return energy - E;
}

double solve() {
    double l = 0, r = 1e5;
    while (r - l > EPS) {
        double mid = (l + r) / 2;
        if (f(mid) > 0) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return l;
}

int main() {
    scanf("%d %lf", &n, &E);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &s[i], &k[i], &v[i]);
    }
    printf("%.6f\n", solve());
    return 0;
}