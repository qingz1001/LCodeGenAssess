#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 3000

typedef struct {
    int x, y;
} Point;

Point bosses[MAX_N];
int n, row, line;

double distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double max(double a, double b) {
    return a > b ? a : b;
}

double min(double a, double b) {
    return a < b ? a : b;
}

double min_distance_to_bosses(double x, double y) {
    double min_dist = 1e9;
    for (int i = 0; i < n; i++) {
        min_dist = min(min_dist, distance(x, y, bosses[i].x, bosses[i].y));
    }
    return min_dist;
}

double binary_search_distance() {
    double low = 0, high = max(row, line);
    double mid;
    while (high - low > 1e-6) {
        mid = (low + high) / 2;
        double dist_to_edge = min(min(mid, row - mid), min(mid, line - mid));
        if (dist_to_edge > min_distance_to_bosses(mid, mid)) {
            low = mid;
        } else {
            high = mid;
        }
    }
    return low;
}

int main() {
    scanf("%d %d %d", &n, &row, &line);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &bosses[i].x, &bosses[i].y);
    }

    double result = binary_search_distance();
    printf("%.2f\n", result);

    return 0;
}