#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-9

typedef struct {
    double x, r, v;
} Base;

int compare(const void *a, const void *b) {
    return ((Base *)a)->x < ((Base *)b)->x ? -1 : 1;
}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double solve(int n, int m, Base bases[], double r_prime[]) {
    double ans = 0.0;
    for (int i = 0; i < n; i++) {
        if (bases[i].x == m) {
            ans += bases[i].v;
            continue;
        }
        double left = bases[i].x - bases[i].r;
        double right = bases[i].x + bases[i].r;
        double min_cost = INFINITY;
        for (int j = 0; j < n; j++) {
            if (j == i || bases[j].x >= bases[i].x) break;
            double d = distance(bases[i].x, 0, bases[j].x, 0);
            if (d <= bases[j].r && d + r_prime[j] >= bases[i].r) {
                double cost = bases[j].v + sqrt(r_prime[j]);
                if (cost < min_cost) {
                    min_cost = cost;
                }
            }
        }
        if (min_cost != INFINITY) {
            ans += min_cost;
        } else {
            ans += bases[i].v;
        }
    }
    return ans;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Base bases[n];
    double r_prime[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &bases[i].x, &bases[i].r, &bases[i].v);
        r_prime[i] = 0.0;
    }
    qsort(bases, n, sizeof(Base), compare);
    printf("%.3f\n", solve(n, m, bases, r_prime));
    return 0;
}