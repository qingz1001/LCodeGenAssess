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

double distance(Circle a, Circle b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double angle(Circle a, Circle b) {
    return acos((a.r - b.r) / distance(a, b));
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &circles[i].r, &circles[i].x, &circles[i].y);
    }

    qsort(circles, n, sizeof(Circle), cmp);

    double result = 2 * PI * circles[0].r;
    for (int i = 1; i < n; i++) {
        int flag = 1;
        for (int j = 0; j < i; j++) {
            double d = distance(circles[i], circles[j]);
            if (d <= fabs(circles[i].r - circles[j].r)) {
                flag = 0;
                break;
            }
            if (d < circles[i].r + circles[j].r) {
                double ang = angle(circles[i], circles[j]);
                result -= 2 * circles[i].r * ang;
            }
        }
        if (flag) result += 2 * PI * circles[i].r;
    }

    printf("%.3f\n", result);
    return 0;
}