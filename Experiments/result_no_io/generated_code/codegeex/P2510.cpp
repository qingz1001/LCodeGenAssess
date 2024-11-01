#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    double x, y, r;
} Circle;

int n;
Circle circles[1001];

double intersectionArea(Circle c1, Circle c2) {
    double d = sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
    if (d > c1.r + c2.r || d < fabs(c1.r - c2.r) || d == 0) {
        return 0;
    }
    double a1 = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    double a2 = acos((c2.r * c2.r + d * d - c1.r * c1.r) / (2 * c2.r * d));
    return a1 * c1.r * c1.r + a2 * c2.r * c2.r - d * c1.r * sin(a1);
}

double calculatePerimeter() {
    double totalPerimeter = 0.0;
    for (int i = 0; i < n; i++) {
        totalPerimeter += 2 * PI * circles[i].r;
        for (int j = 0; j < i; j++) {
            totalPerimeter -= intersectionArea(circles[i], circles[j]) / PI * 2;
        }
    }
    return totalPerimeter;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &circles[i].x, &circles[i].y, &circles[i].r);
    }
    printf("%.3lf\n", calculatePerimeter());
    return 0;
}