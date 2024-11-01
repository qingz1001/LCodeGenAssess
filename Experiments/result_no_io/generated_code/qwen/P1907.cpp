#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1005

typedef struct {
    double x, y;
} Point;

double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double min_unhappiness(double dirt_cost, double rome_cost, int n, Point points[], int roads[MAX_N][MAX_N], Point start, Point end) {
    double dp[MAX_N];
    for (int i = 0; i < n; i++) {
        dp[i] = INFINITY;
    }
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        if (dp[i] == INFINITY) continue;
        for (int j = 0; j < n; j++) {
            if (roads[i][j]) {
                dp[j] = fmin(dp[j], dp[i] + dist(points[i], points[j]) * rome_cost);
            } else {
                dp[j] = fmin(dp[j], dp[i] + dist(points[i], points[j]) * dirt_cost);
            }
        }
    }

    return dp[n-1];
}

int main() {
    double dirt_cost, rome_cost;
    scanf("%lf %lf", &dirt_cost, &rome_cost);

    int n;
    scanf("%d", &n);

    Point points[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    int roads[MAX_N][MAX_N] = {0};
    int i, j;
    while (scanf("%d %d", &i, &j), i != 0 && j != 0) {
        roads[i-1][j-1] = 1;
        roads[j-1][i-1] = 1;
    }

    Point start, end;
    scanf("%lf %lf", &start.x, &start.y);
    scanf("%lf %lf", &end.x, &end.y);

    printf("%.4f\n", min_unhappiness(dirt_cost, rome_cost, n, points, roads, start, end));

    return 0;
}