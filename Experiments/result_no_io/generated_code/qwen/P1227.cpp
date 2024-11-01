#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20000
#define EPS 1e-9

typedef struct {
    double x, y;
} Point;

Point points[MAX_N];
int n;

double sum_x = 0, sum_y = 0;

void read_input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
        sum_x += points[i].x;
        sum_y += points[i].y;
    }
}

Point find_symmetry_center() {
    if (n % 2 == 0) return (Point){sum_x / n, sum_y / n};
    else return points[n / 2];
}

int main() {
    read_input();
    Point center = find_symmetry_center();
    printf("V.I.P. should stay at (%.1f, %.1f).\n", center.x, center.y);
    return 0;
}