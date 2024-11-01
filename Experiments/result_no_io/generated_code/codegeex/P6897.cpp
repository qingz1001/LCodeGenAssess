#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 50000
#define EPS 1e-9

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point p[MAXN];
    int n;
} Path;

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double angle(Point a, Point b) {
    return acos(dot(a, b) / (dist(Point{0, 0}, a) * dist(Point{0, 0}, b)));
}

double solve(Path a, Path b) {
    double ans = INFINITY;
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < b.n; j++) {
            Point dirA = {a.p[(i + 1) % a.n].x - a.p[i].x, a.p[(i + 1) % a.n].y - a.p[i].y};
            Point dirB = {b.p[(j + 1) % b.n].x - b.p[j].x, b.p[(j + 1) % b.n].y - b.p[j].y};
            Point relA = {b.p[j].x - a.p[i].x, b.p[j].y - a.p[i].y};
            Point relB = {a.p[i].x - b.p[j].x, a.p[i].y - b.p[j].y};
            double angleA = angle(dirA, relA);
            double angleB = angle(dirB, relB);
            if (angleA < angleB) {
                double t = dist(a.p[i], b.p[j]) / cos(angleB);
                if (t <= dist(a.p[i], a.p[(i + 1) % a.n]) && t <= dist(b.p[j], b.p[(j + 1) % b.n])) {
                    ans = fmin(ans, t);
                }
            }
        }
    }
    return ans == INFINITY ? -1 : ans;
}

int main() {
    int n, m;
    scanf("%d", &n);
    Path a, b;
    a.n = n;
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &a.p[i].x, &a.p[i].y);
    }
    scanf("%d", &m);
    b.n = m;
    for (int i = 0; i < m; i++) {
        scanf("%lf %lf", &b.p[i].x, &b.p[i].y);
    }
    double result = solve(a, b);
    if (result == -1) {
        printf("impossible\n");
    } else {
        printf("%.6lf\n", result);
    }
    return 0;
}