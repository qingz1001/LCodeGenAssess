#include <stdio.h>
#include <math.h>
#include <float.h>

#define MAXN 1005
#define EPS 1e-8

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point p1, p2;
} Rectangle;

Rectangle rects[MAXN];
Point S, T;
int n;
double v;

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int inside(Point p, Rectangle r) {
    return p.x >= r.p1.x && p.x <= r.p2.x && p.y >= r.p1.y && p.y <= r.p2.y;
}

double solve() {
    double dp[MAXN][4];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 4; j++)
            dp[i][j] = DBL_MAX;
    
    for (int i = 0; i < n; i++) {
        if (inside(S, rects[i])) {
            dp[i][0] = dist(S, rects[i].p1);
            dp[i][1] = dist(S, (Point){rects[i].p2.x, rects[i].p1.y});
            dp[i][2] = dist(S, rects[i].p2);
            dp[i][3] = dist(S, (Point){rects[i].p1.x, rects[i].p2.y});
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(rects[i].p2.x - rects[j].p1.x) < EPS) {
                double y1 = fmax(rects[i].p1.y, rects[j].p1.y);
                double y2 = fmin(rects[i].p2.y, rects[j].p2.y);
                if (y1 <= y2 + EPS) {
                    dp[j][0] = fmin(dp[j][0], dp[i][1] + rects[j].p1.y - y1);
                    dp[j][3] = fmin(dp[j][3], dp[i][2] + y2 - rects[j].p2.y);
                    dp[i][1] = fmin(dp[i][1], dp[j][0] + rects[j].p1.y - y1);
                    dp[i][2] = fmin(dp[i][2], dp[j][3] + y2 - rects[j].p2.y);
                }
            }
        }
    }

    double ans = DBL_MAX;
    for (int i = 0; i < n; i++) {
        if (inside(T, rects[i])) {
            ans = fmin(ans, dp[i][0] + dist(rects[i].p1, T));
            ans = fmin(ans, dp[i][1] + dist((Point){rects[i].p2.x, rects[i].p1.y}, T));
            ans = fmin(ans, dp[i][2] + dist(rects[i].p2, T));
            ans = fmin(ans, dp[i][3] + dist((Point){rects[i].p1.x, rects[i].p2.y}, T));
        }
    }

    return ans / v;
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