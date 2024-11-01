#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WALLS 20
#define INF 1e9

typedef struct {
    double x;
    double a1, b1;
    double a2, b2;
} Wall;

typedef struct {
    double x, y;
} Point;

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double min(double a, double b) {
    return a < b ? a : b;
}

int main() {
    int n;
    Wall walls[MAX_WALLS];
    Point start = {0, 5};
    Point end = {10, 5};

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf %lf %lf", &walls[i].x, &walls[i].a1, &walls[i].b1, &walls[i].a2, &walls[i].b2);
    }

    double dp[MAX_WALLS + 2][4];
    for (int i = 0; i < MAX_WALLS + 2; i++) {
        for (int j = 0; j < 4; j++) {
            dp[i][j] = INF;
        }
    }

    dp[0][0] = distance(start, (Point){walls[0].x, walls[0].a1});
    dp[0][1] = distance(start, (Point){walls[0].x, walls[0].b1});
    dp[0][2] = distance(start, (Point){walls[0].x, walls[0].a2});
    dp[0][3] = distance(start, (Point){walls[0].x, walls[0].b2});

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                Point from, to;
                if (j == 0) from = (Point){walls[i - 1].x, walls[i - 1].a1};
                if (j == 1) from = (Point){walls[i - 1].x, walls[i - 1].b1};
                if (j == 2) from = (Point){walls[i - 1].x, walls[i - 1].a2};
                if (j == 3) from = (Point){walls[i - 1].x, walls[i - 1].b2};

                if (k == 0) to = (Point){walls[i].x, walls[i].a1};
                if (k == 1) to = (Point){walls[i].x, walls[i].b1};
                if (k == 2) to = (Point){walls[i].x, walls[i].a2};
                if (k == 3) to = (Point){walls[i].x, walls[i].b2};

                dp[i][k] = min(dp[i][k], dp[i - 1][j] + distance(from, to));
            }
        }
    }

    double result = INF;
    for (int j = 0; j < 4; j++) {
        Point from;
        if (j == 0) from = (Point){walls[n - 1].x, walls[n - 1].a1};
        if (j == 1) from = (Point){walls[n - 1].x, walls[n - 1].b1};
        if (j == 2) from = (Point){walls[n - 1].x, walls[n - 1].a2};
        if (j == 3) from = (Point){walls[n - 1].x, walls[n - 1].b2};

        result = min(result, dp[n - 1][j] + distance(from, end));
    }

    printf("%.2f\n", result);
    return 0;
}