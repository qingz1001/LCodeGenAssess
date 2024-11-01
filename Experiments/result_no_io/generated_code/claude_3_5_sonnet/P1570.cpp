#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 205

int n, m;
double v[MAXN], c[MAXN];
double f[MAXN];

int cmp(const void *a, const void *b) {
    double fa = *(double*)a;
    double fb = *(double*)b;
    if (fa < fb) return 1;
    if (fa > fb) return -1;
    return 0;
}

int check(double x) {
    for (int i = 0; i < n; i++) {
        f[i] = v[i] - x * c[i];
    }
    qsort(f, n, sizeof(double), cmp);
    double sum = 0;
    for (int i = 0; i < m; i++) {
        sum += f[i];
    }
    return sum >= 0;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &v[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lf", &c[i]);
    }

    double l = 0, r = 1000;
    while (r - l > 1e-6) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    printf("%.3f\n", l);
    return 0;
}