#include <stdio.h>
#include <math.h>

#define MAXN 80005
#define EPS 1e-9

typedef long double ld;

int n, m, q;
ld ax[MAXN], ay[MAXN], at[MAXN];
ld bx[MAXN], by[MAXN], bt[MAXN];

ld dist(ld x1, ld y1, ld x2, ld y2) {
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

ld solve(ld c, int f) {
    int ai = 0, bi = 0, cnt = 0;
    for (ld t = 0; t <= at[n]; t += EPS) {
        while (ai < n && at[ai+1] <= t) ai++;
        while (bi < m && bt[bi+1] <= t) bi++;
        
        ld rx = ax[ai] + (ax[ai+1] - ax[ai]) * (t - at[ai]) / (at[ai+1] - at[ai]);
        ld ry = ay[ai] + (ay[ai+1] - ay[ai]) * (t - at[ai]) / (at[ai+1] - at[ai]);
        ld sx = bx[bi] + (bx[bi+1] - bx[bi]) * (t - bt[bi]) / (bt[bi+1] - bt[bi]);
        ld sy = by[bi] + (by[bi+1] - by[bi]) * (t - bt[bi]) / (bt[bi+1] - bt[bi]);
        
        ld d = dist(rx, ry, sx, sy);
        if (fabs(d - c) < EPS) {
            cnt++;
            if (cnt == f) return t;
        }
    }
    return -4.66;
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    scanf("%Lf%Lf%Lf%Lf", &ax[0], &ay[0], &bx[0], &by[0]);
    
    for (int i = 1; i <= n; i++)
        scanf("%Lf%Lf%Lf", &ax[i], &ay[i], &at[i]);
    
    for (int i = 1; i <= m; i++)
        scanf("%Lf%Lf%Lf", &bx[i], &by[i], &bt[i]);
    
    while (q--) {
        ld c;
        int f;
        scanf("%Lf%d", &c, &f);
        ld ans = solve(c, f);
        printf("%.8Lf\n", ans);
    }
    
    return 0;
}