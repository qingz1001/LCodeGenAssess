#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100005

typedef struct {
    int x, y;
} Point;

Point systems[2];
int n;
Point missiles[MAX_N];

double distance_squared(Point a, Point b) {
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

int main() {
    scanf("%d %d %d %d", &systems[0].x, &systems[0].y, &systems[1].x, &systems[1].y);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &missiles[i].x, &missiles[i].y);
    }

    double min_cost = INFINITY;
    for (int r1 = 0; r1 <= 2000; ++r1) {
        for (int r2 = 0; r2 <= 2000; ++r2) {
            double cost = 0;
            for (int i = 0; i < n; ++i) {
                double d1 = distance_squared(systems[0], missiles[i]);
                double d2 = distance_squared(systems[1], missiles[i]);
                if (d1 > r1 * r1) cost += r1 * r1;
                if (d2 > r2 * r2) cost += r2 * r2;
            }
            if (cost < min_cost) min_cost = cost;
        }
    }

    printf("%.0f\n", min_cost);
    return 0;
}