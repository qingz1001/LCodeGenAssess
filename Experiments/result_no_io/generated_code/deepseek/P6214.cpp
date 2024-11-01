#include <stdio.h>
#include <math.h>

#define MAXN 80005
#define MAXQ 300005
#define EPS 1e-7

typedef struct {
    double x, y, t;
} Point;

Point A[MAXN], B[MAXN];
double c[MAXQ];
int f[MAXQ];
double results[MAXQ];

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double interpolate(double t, Point p1, Point p2) {
    double ratio = (t - p1.t) / (p2.t - p1.t);
    return (1 - ratio) * p1.x + ratio * p2.x;
}

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);

    scanf("%lf %lf %lf %lf", &A[0].x, &A[0].y, &B[0].x, &B[0].y);
    A[0].t = B[0].t = 0;

    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf %lf", &A[i].x, &A[i].y, &A[i].t);
    }

    for (int i = 1; i <= m; i++) {
        scanf("%lf %lf %lf", &B[i].x, &B[i].y, &B[i].t);
    }

    for (int i = 0; i < q; i++) {
        scanf("%lf %d", &c[i], &f[i]);
    }

    for (int i = 0; i < q; i++) {
        int count = 0;
        double last_time = -1;
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= m; k++) {
                if (A[j].t > B[k].t) continue;
                double t1 = A[j].t, t2 = B[k].t;
                double t_min = t1, t_max = t2;
                while (t_max - t_min > EPS) {
                    double t_mid = (t_min + t_max) / 2;
                    double Ax = interpolate(t_mid, A[j], A[j + 1]);
                    double Ay = interpolate(t_mid, A[j], A[j + 1]);
                    double Bx = interpolate(t_mid, B[k], B[k + 1]);
                    double By = interpolate(t_mid, B[k], B[k + 1]);
                    double dist = distance(Ax, Ay, Bx, By);
                    if (fabs(dist - c[i]) < EPS) {
                        if (last_time < 0 || fabs(t_mid - last_time) > EPS) {
                            count++;
                            last_time = t_mid;
                        }
                        if (count == f[i]) {
                            results[i] = t_mid;
                            break;
                        }
                    }
                    if (dist < c[i]) {
                        t_max = t_mid;
                    } else {
                        t_min = t_mid;
                    }
                }
                if (results[i] >= 0) break;
            }
            if (results[i] >= 0) break;
        }
        if (results[i] < 0) {
            if (count == 0) {
                results[i] = -4.66;
            } else {
                results[i] = -2.33;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        printf("%.8lf\n", results[i]);
    }

    return 0;
}