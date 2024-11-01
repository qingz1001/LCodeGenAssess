#include <stdio.h>
#include <math.h>

#define MAXN 1000

typedef struct {
    double x, y, r;
} Circle;

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double calculate_perimeter(Circle circles[], int n) {
    double total_perimeter = 0.0;
    for (int i = 0; i < n; i++) {
        double perimeter = 2 * M_PI * circles[i].r;
        for (int j = 0; j < i; j++) {
            double d = distance(circles[i].x, circles[i].y, circles[j].x, circles[j].y);
            if (d < circles[j].r - circles[i].r) {
                perimeter = 0.0;
                break;
            } else if (d < circles[i].r - circles[j].r) {
                continue;
            } else if (d < circles[i].r + circles[j].r) {
                double alpha = acos((circles[i].r * circles[i].r + d * d - circles[j].r * circles[j].r) / (2 * circles[i].r * d));
                double beta = acos((circles[j].r * circles[j].r + d * d - circles[i].r * circles[i].r) / (2 * circles[j].r * d));
                perimeter -= 2 * alpha * circles[i].r;
            }
        }
        total_perimeter += perimeter;
    }
    return total_perimeter;
}

int main() {
    int n;
    Circle circles[MAXN];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &circles[i].r, &circles[i].x, &circles[i].y);
    }

    double result = calculate_perimeter(circles, n);
    printf("%.3lf\n", result);

    return 0;
}