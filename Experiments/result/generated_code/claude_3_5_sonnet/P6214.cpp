#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAXN 80005
#define EPS 1e-9

typedef struct {
    double x, y, t;
} Point;

Point A[MAXN], B[MAXN];
int n, m, q;

double sqr(double x) { return x * x; }

double dist(double x1, double y1, double x2, double y2) {
    return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}

bool check(double t, double c, int ai, int bi) {
    double ax = A[ai].x + (A[ai+1].x - A[ai].x) * (t - A[ai].t) / (A[ai+1].t - A[ai].t);
    double ay = A[ai].y + (A[ai+1].y - A[ai].y) * (t - A[ai].t) / (A[ai+1].t - A[ai].t);
    double bx = B[bi].x + (B[bi+1].x - B[bi].x) * (t - B[bi].t) / (B[bi+1].t - B[bi].t);
    double by = B[bi].y + (B[bi+1].y - B[bi].y) * (t - B[bi].t) / (B[bi+1].t - B[bi].t);
    return fabs(dist(ax, ay, bx, by) - c) < EPS;
}

double solve(double c, int f) {
    int ai = 0, bi = 0, cnt = 0;
    double l, r, mid;
    
    while (ai < n && bi < m) {
        l = fmax(A[ai].t, B[bi].t);
        r = fmin(A[ai+1].t, B[bi+1].t);
        
        if (check(l, c, ai, bi) && check(r, c, ai, bi)) {
            if (++cnt == f) return l;
            if (fabs(r - l) > EPS) return -2.33;
        } else if (check(l, c, ai, bi) || check(r, c, ai, bi)) {
            for (int i = 0; i < 100; i++) {
                mid = (l + r) / 2;
                if (check(mid, c, ai, bi)) {
                    if (++cnt == f) return mid;
                    break;
                }
                if ((check(l, c, ai, bi) && !check(mid, c, ai, bi)) ||
                    (!check(l, c, ai, bi) && check(mid, c, ai, bi)))
                    r = mid;
                else
                    l = mid;
            }
        }
        
        if (A[ai+1].t < B[bi+1].t) ai++;
        else if (A[ai+1].t > B[bi+1].t) bi++;
        else { ai++; bi++; }
    }
    
    return -4.66;
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    scanf("%lf%lf%lf%lf", &A[0].x, &A[0].y, &B[0].x, &B[0].y);
    A[0].t = B[0].t = 0;
    
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf", &A[i].x, &A[i].y, &A[i].t);
    for (int i = 1; i <= m; i++)
        scanf("%lf%lf%lf", &B[i].x, &B[i].y, &B[i].t);
    
    double c;
    int f;
    for (int i = 0; i < q; i++) {
        scanf("%lf%d", &c, &f);
        printf("%.8f\n", solve(c, f));
    }
    
    return 0;
}