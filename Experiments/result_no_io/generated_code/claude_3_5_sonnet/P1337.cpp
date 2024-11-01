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

void calculate_balance(double *rx, double *ry) {
    double x = 0, y = 0, total_w = 0;
    for (int i = 0; i < n; i++) {
        x += points[i].x * points[i].w;
        y += points[i].y * points[i].w;
        total_w += points[i].w;
    }
    x /= total_w;
    y /= total_w;

    while (1) {
        double fx = 0, fy = 0;
        for (int i = 0; i < n; i++) {
            double d = dist(x, y, points[i]);
            if (d > EPS) {
                fx += points[i].w * (points[i].x - x) / d;
                fy += points[i].w * (points[i].y - y) / d;
            }
        }
        double f = sqrt(fx * fx + fy * fy);
        if (f < EPS) break;
        x += fx / f * 0.1;
        y += fy / f * 0.1;
    }

    *rx = x;
    *ry = y;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %d", &points[i].x, &points[i].y, &points[i].w);
    }

    double result_x, result_y;
    calculate_balance(&result_x, &result_y);

    printf("%.3f %.3f\n", result_x, result_y);

    return 0;
}