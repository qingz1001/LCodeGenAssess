#include <stdio.h>
#include <math.h>

#define EPS 1e-9

typedef struct {
    double x, y;
} Point;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int n;
    scanf("%d", &n);
    Point disks[n];
    for (int i = 0; i < n; ++i) {
        scanf("%lf %lf %lf", &disks[i].x, &disks[i].y, &disks[i].x);
    }

    double perimeter = 0.0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double d = distance(disks[i], disks[j]);
            if (fabs(d - (disks[i].x + disks[j].x)) < EPS) {
                perimeter += M_PI * (disks[i].x + disks[j].x);
            }
        }
    }

    printf("%.3f\n", perimeter);
    return 0;
}