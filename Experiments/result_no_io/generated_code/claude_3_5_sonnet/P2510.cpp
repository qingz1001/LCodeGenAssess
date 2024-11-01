#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_N 1000
#define PI 3.14159265358979323846

typedef struct {
    double r, x, y;
} Circle;

Circle circles[MAX_N];
int n;

int cmp(const void *a, const void *b) {
    Circle *ca = (Circle *)a;
    Circle *cb = (Circle *)b;
    return (ca->y > cb->y) ? -1 : 1;
}

double dist(Circle a, Circle b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int intersect(Circle a, Circle b) {
    double d = dist(a, b);
    return d < a.r + b.r;
}

double angle(Circle a, Circle b) {
    double d = dist(a, b);
    return acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d));
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &circles[i].r, &circles[i].x, &circles[i].y);
    }

    qsort(circles, n, sizeof(Circle), cmp);

    double perimeter = 0;
    for (int i = 0; i < n; i++) {
        double ang = 2 * PI;
        for (int j = 0; j < i; j++) {
            if (intersect(circles[i], circles[j])) {
                ang -= 2 * angle(circles[i], circles[j]);
            }
        }
        perimeter += ang * circles[i].r;
    }

    printf("%.3f\n", perimeter);
    return 0;
}