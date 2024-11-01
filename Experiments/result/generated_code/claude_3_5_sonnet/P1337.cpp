#include <stdio.h>
#include <math.h>

#define MAX_N 1000
#define EPS 1e-6

typedef struct {
    double x, y;
    int w;
} Point;

Point points[MAX_N];
int n;

double dist(double x, double y, Point p) {
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

void calc(double x, double y, double* fx, double* fy) {
    *fx = *fy = 0;
    for (int i = 0; i < n; i++) {
        double d = dist(x, y, points[i]);
        if (d < EPS) continue;
        *fx += points[i].w * (x - points[i].x) / d;
        *fy += points[i].w * (y - points[i].y) / d;
    }
}

int main() {
    scanf("%d", &n);
    double sumx = 0, sumy = 0, sumw = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf%d", &points[i].x, &points[i].y, &points[i].w);
        sumx += points[i].x * points[i].w;
        sumy += points[i].y * points[i].w;
        sumw += points[i].w;
    }

    double x = sumx / sumw, y = sumy / sumw;
    double fx, fy;
    for (int i = 0; i < 100000; i++) {
        calc(x, y, &fx, &fy);
        if (fabs(fx) < EPS && fabs(fy) < EPS) break;
        x += fx / sumw;
        y += fy / sumw;
    }

    printf("%.3f %.3f\n", x, y);
    return 0;
}