#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y, t;
} Point;

double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double find_time(Point start, Point end, double c) {
    if (start.t == end.t) {
        return c / distance(start, end);
    }
    double v = distance(start, end) / (end.t - start.t);
    double a = (v * v - c * c) / (2 * (start.t * end.t - start.t * start.t - end.t * end.t + start.t * end.t));
    if (a < 0) return -2.33;
    double b = v - 2 * a * start.t;
    double discriminant = b * b - 4 * a * (start.t * start.t - c * c / (a * a));
    if (discriminant < 0) return -2.33;
    double t1 = (-b + sqrt(discriminant)) / (2 * a);
    double t2 = (-b - sqrt(discriminant)) / (2 * a);
    if (t1 > 0 && t1 <= end.t) return t1;
    if (t2 > 0 && t2 <= end.t) return t2;
    return -2.33;
}

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    Point Ax0, Ay0, Bx0, By0;
    scanf("%lf %lf %lf %lf", &Ax0.x, &Ax0.y, &Ay0.x, &Ay0.y);
    Point A[n];
    Point B[m];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &A[i].x, &A[i].y, &A[i].t);
    }
    for (int i = 0; i < m; i++) {
        scanf("%lf %lf %lf", &B[i].x, &B[i].y, &B[i].t);
    }
    for (int i = 0; i < q; i++) {
        double c;
        int f;
        scanf("%lf %d", &c, &f);
        if (f > n + m) {
            printf("-4.66\n");
            continue;
        }
        if (f <= n) {
            double time = find_time(Ax0, A[f], c);
            if (time == -2.33 || time > A[f].t) {
                printf("-4.66\n");
            } else {
                printf("%.8lf\n", time);
            }
        } else {
            double time = find_time(Bx0, B[f - n], c);
            if (time == -2.33 || time > B[f - n].t) {
                printf("-4.66\n");
            } else {
                printf("%.8lf\n", time);
            }
        }
    }
    return 0;
}