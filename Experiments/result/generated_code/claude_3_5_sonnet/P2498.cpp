#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 3000
#define MAX_ROW 1000
#define MAX_LINE 1000
#define INF 1e9

typedef struct {
    double x, y;
} Point;

Point bosses[MAX_N];
int n, row, line;

double min(double a, double b) {
    return a < b ? a : b;
}

double max(double a, double b) {
    return a > b ? a : b;
}

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double check(double mid) {
    double left = 0, right = row, top = line, bottom = 0;
    for (int i = 0; i < n; i++) {
        left = max(left, bosses[i].x - mid);
        right = min(right, bosses[i].x + mid);
        bottom = max(bottom, bosses[i].y - mid);
        top = min(top, bosses[i].y + mid);
    }
    return left <= right && bottom <= top;
}

int main() {
    scanf("%d %d %d", &n, &row, &line);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &bosses[i].x, &bosses[i].y);
    }

    double left = 0, right = INF;
    while (right - left > 1e-6) {
        double mid = (left + right) / 2;
        if (check(mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    printf("%.2f\n", left);
    return 0;
}