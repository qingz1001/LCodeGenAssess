#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 80001
#define MAXM 300001
#define EPS 1e-9

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point p;
    double t;
} Event;

int cmp(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    if (e1->t < e2->t) return -1;
    if (e1->t > e2->t) return 1;
    return 0;
}

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);

    Point A0, B0;
    scanf("%lf%lf%lf%lf", &A0.x, &A0.y, &B0.x, &B0.y);

    Event events[MAXM];
    int eventCount = 0;

    for (int i = 0; i < n; i++) {
        Point A;
        double At;
        scanf("%lf%lf%lf", &A.x, &A.y, &At);
        events[eventCount++] = (Event){A0, At};
        events[eventCount++] = (Event){A, At};
        A0 = A;
    }

    for (int i = 0; i < m; i++) {
        Point B;
        double Bt;
        scanf("%lf%lf%lf", &B.x, &B.y, &Bt);
        events[eventCount++] = (Event){B0, Bt};
        events[eventCount++] = (Event){B, Bt};
        B0 = B;
    }

    qsort(events, eventCount, sizeof(Event), cmp);

    for (int i = 0; i < q; i++) {
        double c;
        int f;
        scanf("%lf%d", &c, &f);

        int count = 0;
        double prevTime = -1;
        for (int j = 0; j < eventCount; j++) {
            Event e = events[j];
            if (e.t != prevTime) {
                count = 0;
                prevTime = e.t;
            }
            if (count >= f) {
                Point p1 = events[j - 2].p;
                Point p2 = events[j - 1].p;
                double t1 = events[j - 2].t;
                double t2 = events[j - 1].t;
                double d = dist(p1, p2);
                double dt = t2 - t1;
                double v = d / dt;
                double t = (c - dist(p1, B0)) / v;
                if (t >= t1 && t <= t2) {
                    printf("%.8Lf\n", t1 + t);
                    break;
                }
            }
            count++;
        }
    }

    return 0;
}