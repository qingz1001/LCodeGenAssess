#include <stdio.h>
#include <math.h>
#include <float.h>

#define MAX_N 50000
#define EPS 1e-9

typedef struct {
    double x, y;
} Point;

Point misha[MAX_N], nadia[MAX_N];
int n, m;

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Point interpolate(Point a, Point b, double t) {
    Point res;
    res.x = a.x + (b.x - a.x) * t;
    res.y = a.y + (b.y - a.y) * t;
    return res;
}

double solve() {
    double ans = DBL_MAX;
    double tm = 0, tn = 0;
    int im = 0, in = 0;
    
    while (im < n - 1 || in < m - 1) {
        double dm = (im < n - 1) ? dist(misha[im], misha[im+1]) : DBL_MAX;
        double dn = (in < m - 1) ? dist(nadia[in], nadia[in+1]) : DBL_MAX;
        double step = fmin(dm, dn);
        
        for (double t = 0; t <= 1; t += 0.01) {
            Point pm = interpolate(misha[im], misha[im+1], t);
            Point pn = interpolate(nadia[in], nadia[in+1], t);
            double d = dist(pm, pn);
            if (tm + t*step + d <= tn + t*step) {
                ans = fmin(ans, d);
            }
        }
        
        if (dm < dn + EPS) {
            tm += dm;
            im++;
        }
        if (dn < dm + EPS) {
            tn += dn;
            in++;
        }
    }
    
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &misha[i].x, &misha[i].y);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%lf %lf", &nadia[i].x, &nadia[i].y);
    }
    
    double ans = solve();
    if (ans > 1e6) {
        printf("impossible\n");
    } else {
        printf("%.3f\n", ans);
    }
    
    return 0;
}