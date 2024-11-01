#include <stdio.h>
#include <math.h>

#define MAX_N 5000

typedef struct {
    double x, y;
} Point;

Point points[MAX_N];
int n;

double max(double a, double b) {
    return a > b ? a : b;
}

double calculateY(double x, Point p1, Point p2) {
    if (p1.x == p2.x) return max(p1.y, p2.y);
    return p1.y + (p2.y - p1.y) * (x - p1.x) / (p2.x - p1.x);
}

double findMinY() {
    double left = points[0].x;
    double right = points[n-1].x;
    double minY = 1e9;

    while (right - left > 1e-6) {
        double mid = (left + right) / 2;
        double maxY = -1;

        for (int i = 0; i < n - 1; i++) {
            double y = calculateY(mid, points[i], points[i+1]);
            if (y > maxY) maxY = y;
        }

        if (maxY < minY) minY = maxY;

        double leftY = -1, rightY = -1;
        for (int i = 0; i < n - 1; i++) {
            leftY = max(leftY, calculateY(left, points[i], points[i+1]));
            rightY = max(rightY, calculateY(right, points[i], points[i+1]));
        }

        if (leftY > rightY) left = mid;
        else right = mid;
    }

    return minY;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    double result = findMinY();
    printf("%.2f\n", result);

    return 0;
}