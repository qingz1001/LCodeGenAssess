#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 5000
#define EPS 1e-6

typedef struct {
    double x, y;
} Point;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int n;
    scanf("%d", &n);
    Point cities[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &cities[i].x, &cities[i].y);
    }

    double total_length = 0.0;
    for (int i = 0; i < n; i++) {
        double min_dist = INFINITY;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double dist = distance(cities[i], cities[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                }
            }
        }
        total_length += min_dist;
    }

    printf("%.2lf\n", total_length);
    return 0;
}