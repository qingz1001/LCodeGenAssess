#include <stdio.h>
#include <math.h>
#include <limits.h>

#define MAX_N 1005
#define INF INT_MAX

typedef struct {
    double x, y;
} Point;

double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int main() {
    double dirt_cost, rome_cost;
    scanf("%lf %lf", &dirt_cost, &rome_cost);
    int N;
    scanf("%d", &N);
    Point points[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    int roads[MAX_N][MAX_N] = {0};
    int u, v;
    while (scanf("%d %d", &u, &v), u != 0 && v != 0) {
        roads[u-1][v-1] = 1;
        roads[v-1][u-1] = 1;
    }
    Point dock, home;
    scanf("%lf %lf", &dock.x, &dock.y);
    scanf("%lf %lf", &home.x, &home.y);

    double dp[MAX_N][2];
    for (int i = 0; i < N; i++) {
        dp[i][0] = dp[i][1] = INF;
    }
    dp[0][0] = 0;
    dp[0][1] = dist(points[0], dock) * dirt_cost;

    for (int i = 1; i < N; i++) {
        dp[i][0] = INF;
        dp[i][1] = INF;
        for (int j = 0; j < N; j++) {
            if (roads[j][i]) {
                dp[i][0] = fmin(dp[i][0], dp[j][0] + dist(points[j], points[i]));
                dp[i][1] = fmin(dp[i][1], dp[j][1] + dist(points[j], points[i]));
            } else {
                dp[i][0] = fmin(dp[i][0], dp[j][0] + dist(points[j], points[i]));
                dp[i][1] = fmin(dp[i][1], dp[j][1] + dist(points[j], points[i]) * dirt_cost);
            }
        }
    }

    double min_cost = INF;
    for (int i = 0; i < N; i++) {
        min_cost = fmin(min_cost, dp[i][0] + dist(points[i], home));
        min_cost = fmin(min_cost, dp[i][1] + dist(points[i], home) * dirt_cost);
    }

    printf("%.4f\n", min_cost);
    return 0;
}