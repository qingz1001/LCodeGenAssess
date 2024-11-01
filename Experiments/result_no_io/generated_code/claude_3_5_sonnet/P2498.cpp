#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 3000
#define EPS 1e-6

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

double dist(double x, double y, Point p) {
    return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

double min_dist(double x, double y) {
    double min_d = 1e9;
    for (int i = 0; i < n; i++) {
        min_d = min(min_d, dist(x, y, bosses[i]));
    }
    return min_d;
}

double check(double mid) {
    double left = 0, right = row, up = line, down = 0;
    for (int i = 0; i < n; i++) {
        if (bosses[i].x - mid <= 0) left = max(left, bosses[i].x + mid);
        if (bosses[i].x + mid >= row) right = min(right, bosses[i].x - mid);
        if (bosses[i].y - mid <= 0) down = max(down, bosses[i].y + mid);
        if (bosses[i].y + mid >= line) up = min(up, bosses[i].y - mid);
    }
    return (left <= right && down <= up);
}

int main() {
    scanf("%d %d %d", &n, &row, &line);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &bosses[i].x, &bosses[i].y);
    }

    double left = 0, right = min(row, line);
    while (right - left > EPS) {
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