#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-7

typedef struct {
    double x, y, t;
} Point;

double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double find_time(Point start, Point end, double target_dist) {
    if (start.t == end.t) return -1;
    double v = distance(start, end) / (end.t - start.t);
    if (v <= 0) return -1;
    double t = (target_dist * v - distance(start, end)) / (-v);
    if (t < 0 || t > end.t - start.t) return -1;
    return start.t + t;
}

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);

    Point A0, B0;
    scanf("%lf %lf %lf %lf", &A0.x, &A0.y, &B0.x, &B0.y);

    Point A[n], B[m];
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

        int count = 0;
        for (int j = 0; j < n - 1; j++) {
            for (int k = 0; k < m - 1; k++) {
                double ta = find_time(A[j], A[j + 1], c);
                double tb = find_time(B[k], B[k + 1], c);
                if (ta != -1 && tb != -1) {
                    if (ta <= tb && ta >= 0) {
                        count++;
                        if (count == f) {
                            printf("%.8f\n", ta);
                            goto next_query;
                        }
                    } else if (tb <= ta && tb >= 0) {
                        count++;
                        if (count == f) {
                            printf("%.8f\n", tb);
                            goto next_query;
                        }
                    }
                }
            }
        }

        if (count < f) {
            printf("-4.66\n");
        } else {
            printf("-2.33\n");
        }

next_query:;
    }

    return 0;
}