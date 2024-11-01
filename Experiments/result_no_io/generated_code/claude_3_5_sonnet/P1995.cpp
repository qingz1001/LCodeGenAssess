#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_N 100005
#define EPS 1e-8

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point p1, p2;
} Rectangle;

Rectangle rects[MAX_N];
int n;
Point S, T;
double v;

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int cmp(const void *a, const void *b) {
    Rectangle *ra = (Rectangle *)a;
    Rectangle *rb = (Rectangle *)b;
    if (fabs(ra->p1.x - rb->p1.x) < EPS) return 0;
    return ra->p1.x < rb->p1.x ? -1 : 1;
}

double solve() {
    qsort(rects, n, sizeof(Rectangle), cmp);
    
    double dp[MAX_N][2];
    dp[0][0] = dist(S, rects[0].p1);
    dp[0][1] = dist(S, rects[0].p2);
    
    for (int i = 1; i < n; i++) {
        dp[i][0] = fmin(dp[i-1][0] + dist(rects[i-1].p1, rects[i].p1),
                        dp[i-1][1] + dist(rects[i-1].p2, rects[i].p1));
        dp[i][1] = fmin(dp[i-1][0] + dist(rects[i-1].p1, rects[i].p2),
                        dp[i-1][1] + dist(rects[i-1].p2, rects[i].p2));
    }
    
    double result = fmin(dp[n-1][0] + dist(rects[n-1].p1, T),
                         dp[n-1][1] + dist(rects[n-1].p2, T));
    
    return result / v;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf%lf%lf", &rects[i].p1.x, &rects[i].p1.y, &rects[i].p2.x, &rects[i].p2.y);
    }
    scanf("%lf%lf", &S.x, &S.y);
    scanf("%lf%lf", &T.x, &T.y);
    scanf("%lf", &v);
    
    printf("%.6f\n", solve());
    
    return 0;
}