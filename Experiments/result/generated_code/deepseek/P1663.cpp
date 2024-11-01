#include <stdio.h>
#include <math.h>

#define MAXN 5000

typedef struct {
    double x, y;
} Point;

Point points[MAXN];

double calculateY(int n, double x) {
    double y = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x > x) {
            double slope = (points[i].y - points[i-1].y) / (points[i].x - points[i-1].x);
            y = points[i-1].y + slope * (x - points[i-1].x);
            break;
        }
    }
    return y;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    double minY = 1e9;
    for (int i = 1; i < n; i++) {
        double midX = (points[i].x + points[i-1].x) / 2;
        double midY = (points[i].y + points[i-1].y) / 2;
        double y = calculateY(n, midX);
        if (y < minY) {
            minY = y;
        }
    }

    printf("%.2f\n", minY);
    return 0;
}