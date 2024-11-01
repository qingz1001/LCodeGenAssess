#include <stdio.h>
#include <math.h>

#define MAXN 1000

typedef struct {
    double x, y, r;
} Circle;

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double calculateArcLength(Circle c1, Circle c2) {
    double d = distance(c1.x, c1.y, c2.x, c2.y);
    if (d >= c1.r + c2.r) {
        return 0.0;
    }
    if (d <= fabs(c1.r - c2.r)) {
        return 2 * M_PI * fmin(c1.r, c2.r);
    }
    double alpha = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    double beta = acos((c2.r * c2.r + d * d - c1.r * c1.r) / (2 * c2.r * d));
    return c1.r * (2 * alpha) + c2.r * (2 * beta);
}

int main() {
    int n;
    Circle circles[MAXN];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &circles[i].r, &circles[i].x, &circles[i].y);
    }

    double totalPerimeter = 0.0;
    for (int i = 0; i < n; i++) {
        double coveredPerimeter = 0.0;
        for (int j = i + 1; j < n; j++) {
            coveredPerimeter += calculateArcLength(circles[i], circles[j]);
        }
        totalPerimeter += 2 * M_PI * circles[i].r - coveredPerimeter;
    }

    printf("%.3lf\n", totalPerimeter);
    return 0;
}