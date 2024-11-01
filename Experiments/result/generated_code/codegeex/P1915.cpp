#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SHRIMP_NUM 100
#define MAX_TIME 1000.0

typedef struct {
    double weight;
    double x, y;
    double vx, vy;
} Shrimp;

typedef struct {
    double t, x, y;
    int shrimp_id;
} Event;

int cmp(const void *a, const void *b) {
    double dist_a = ((Event *)a)->t;
    double dist_b = ((Event *)b)->t;
    if (dist_a < dist_b) return -1;
    if (dist_a > dist_b) return 1;
    return 0;
}

int main() {
    double w0, V, T, x0, y0;
    int n;
    scanf("%lf %lf %lf %lf %lf", &w0, &V, &T, &x0, &y0);
    scanf("%d", &n);

    Shrimp shrimps[MAX_SHRIMP_NUM];
    Event events[MAX_SHRIMP_NUM];

    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf %lf %lf", &shrimps[i].weight, &shrimps[i].x, &shrimps[i].y, &shrimps[i].vx, &shrimps[i].vy);
    }

    for (int i = 0; i < n; i++) {
        double dt = (w0 - shrimps[i].weight) / (w0 * shrimps[i].vx);
        double t = dt < T ? dt : T;
        double x = x0 + w0 * t * shrimps[i].vx;
        double y = y0 + w0 * t * shrimps[i].vy;
        events[i] = (Event){t, x, y, i};
    }

    qsort(events, n, sizeof(Event), cmp);

    int eaten_count = 0;
    double total_weight = 0.0;

    for (int i = 0; i < n; i++) {
        if (events[i].t <= T && events[i].t > 0 && events[i].x >= 0 && events[i].y >= 0) {
            eaten_count++;
            total_weight += shrimps[events[i].shrimp_id].weight;
            w0 += shrimps[events[i].shrimp_id].weight;
            printf("%.6lf %.6lf %.6lf %d\n", events[i].t, events[i].x, events[i].y, events[i].shrimp_id + 1);
        }
    }

    printf("%d\n", eaten_count);
    printf("%.6lf\n", total_weight);

    return 0;
}