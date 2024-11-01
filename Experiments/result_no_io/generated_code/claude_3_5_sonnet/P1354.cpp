#include <stdio.h>
#include <math.h>
#include <float.h>

#define MAX_N 20
#define MAX_POINTS 42

typedef struct {
    double x, y;
} Point;

typedef struct {
    double x;
    double y1, y2, y3, y4;
} Wall;

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int n;
Wall walls[MAX_N];
Point points[MAX_POINTS];
int pointCount;
double dp[MAX_POINTS];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf %lf %lf", &walls[i].x, &walls[i].y1, &walls[i].y2, &walls[i].y3, &walls[i].y4);
    }

    points[pointCount++] = (Point){0, 5};
    for (int i = 0; i < n; i++) {
        points[pointCount++] = (Point){walls[i].x, walls[i].y1};
        points[pointCount++] = (Point){walls[i].x, walls[i].y2};
        points[pointCount++] = (Point){walls[i].x, walls[i].y3};
        points[pointCount++] = (Point){walls[i].x, walls[i].y4};
    }
    points[pointCount++] = (Point){10, 5};

    for (int i = 0; i < pointCount; i++) {
        dp[i] = DBL_MAX;
    }
    dp[0] = 0;

    for (int i = 0; i < pointCount; i++) {
        for (int j = i + 1; j < pointCount; j++) {
            if (points[j].x > points[i].x) {
                int canReach = 1;
                for (int k = 0; k < n; k++) {
                    if (walls[k].x > points[i].x && walls[k].x < points[j].x) {
                        if (points[i].y < walls[k].y1 || points[i].y > walls[k].y4 ||
                            points[j].y < walls[k].y1 || points[j].y > walls[k].y4) {
                            canReach = 0;
                            break;
                        }
                        if ((points[i].y < walls[k].y2 && points[j].y > walls[k].y3) ||
                            (points[i].y > walls[k].y3 && points[j].y < walls[k].y2)) {
                            canReach = 0;
                            break;
                        }
                    }
                }
                if (canReach) {
                    double newDist = dp[i] + dist(points[i], points[j]);
                    if (newDist < dp[j]) {
                        dp[j] = newDist;
                    }
                }
            }
        }
    }

    printf("%.2f\n", dp[pointCount - 1]);
    return 0;
}