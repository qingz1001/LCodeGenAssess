#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EPS 1e-7
#define MAXN 80000
#define MAXQ 300000

typedef struct {
    double x, y, t;
} Point;

Point A[MAXN + 1], B[MAXN + 1];
int n, m, q;

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double interpolate(double t, Point p1, Point p2) {
    double ratio = (t - p1.t) / (p2.t - p1.t);
    return p1.x + ratio * (p2.x - p1.x), p1.y + ratio * (p2.y - p1.y);
}

int compare(const void *a, const void *b) {
    double diff = *(double *)a - *(double *)b;
    return diff > 0 ? 1 : (diff < 0 ? -1 : 0);
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    scanf("%lf %lf %lf %lf", &A[0].x, &A[0].y, &B[0].x, &B[0].y);
    A[0].t = B[0].t = 0;

    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf %lf", &A[i].x, &A[i].y, &A[i].t);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%lf %lf %lf", &B[i].x, &B[i].y, &B[i].t);
    }

    double distances[MAXQ];
    int count = 0;

    for (int i = 0; i < q; i++) {
        double c;
        int f;
        scanf("%lf %d", &c, &f);

        double times[MAXN + MAXN];
        int time_count = 0;

        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                double t1 = A[j].t, t2 = A[j + 1].t;
                double t3 = B[k].t, t4 = B[k + 1].t;

                if (t2 < t3 || t4 < t1) continue;

                double start = fmax(t1, t3);
                double end = fmin(t2, t4);

                while (start <= end) {
                    double mid = (start + end) / 2;
                    double Ax, Ay, Bx, By;
                    Ax = interpolate(mid, A[j], A[j + 1]);
                    Ay = interpolate(mid, A[j], A[j + 1]);
                    Bx = interpolate(mid, B[k], B[k + 1]);
                    By = interpolate(mid, B[k], B[k + 1]);

                    double dist = distance(Ax, Ay, Bx, By);
                    if (fabs(dist - c) < EPS) {
                        times[time_count++] = mid;
                    }

                    if (dist < c) {
                        end = mid - EPS;
                    } else {
                        start = mid + EPS;
                    }
                }
            }
        }

        qsort(times, time_count, sizeof(double), compare);

        if (time_count == 0) {
            printf("-4.66\n");
        } else if (time_count == 1) {
            printf("-2.33\n");
        } else {
            if (f > time_count) {
                printf("-4.66\n");
            } else {
                printf("%.8lf\n", times[f - 1]);
            }
        }
    }

    return 0;
}