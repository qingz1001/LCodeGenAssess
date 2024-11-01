#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-6
#define MAXN 8000

int n, k, p;
int h[MAXN];

typedef struct {
    double a;
} Decimal;

Decimal decimal_add(Decimal x, Decimal y) {
    Decimal res;
    res.a = x.a + y.a;
    return res;
}

Decimal decimal_sub(Decimal x, Decimal y) {
    Decimal res;
    res.a = x.a - y.a;
    return res;
}

Decimal decimal_mul(Decimal x, Decimal y) {
    Decimal res;
    res.a = x.a * y.a;
    return res;
}

Decimal decimal_div(Decimal x, Decimal y) {
    Decimal res;
    res.a = x.a / y.a;
    return res;
}

int compare(Decimal x, Decimal y) {
    if (fabs(x.a - y.a) < EPS) {
        return 0;
    } else if (x.a > y.a) {
        return 1;
    } else {
        return -1;
    }
}

Decimal solve(int n, int k, int h[]) {
    Decimal res;
    res.a = 0;
    for (int i = 0; i < n; i++) {
        res.a += h[i];
    }
    res.a /= n;
    return res;
}

int main() {
    scanf("%d %d %d", &n, &k, &p);
    for (int i = 0; i < n; i++) {
        scanf("%d", &h[i]);
    }

    Decimal ans = solve(n, k, h);
    printf("%.6lf\n", ans.a);

    return 0;
}