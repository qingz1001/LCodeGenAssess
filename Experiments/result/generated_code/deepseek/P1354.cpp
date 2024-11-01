#include <stdio.h>
#include <math.h>

#define MAX_WALLS 20
#define INF 1e9

typedef struct {
    double x, a1, b1, a2, b2;
} Wall;

Wall walls[MAX_WALLS];
int n;

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double min(double a, double b) {
    return a < b ? a : b;
}

double shortestPath(double x, double y, int wallIndex) {
    if (wallIndex == n) {
        return distance(x, y, 10, 5);
    }

    Wall wall = walls[wallIndex];
    double minDist = INF;

    // Try passing through the first gap
    if (y >= wall.a1 && y <= wall.b1) {
        minDist = min(minDist, shortestPath(wall.x, y, wallIndex + 1));
    } else {
        minDist = min(minDist, distance(x, y, wall.x, wall.a1) + shortestPath(wall.x, wall.a1, wallIndex + 1));
        minDist = min(minDist, distance(x, y, wall.x, wall.b1) + shortestPath(wall.x, wall.b1, wallIndex + 1));
    }

    // Try passing through the second gap
    if (y >= wall.a2 && y <= wall.b2) {
        minDist = min(minDist, shortestPath(wall.x, y, wallIndex + 1));
    } else {
        minDist = min(minDist, distance(x, y, wall.x, wall.a2) + shortestPath(wall.x, wall.a2, wallIndex + 1));
        minDist = min(minDist, distance(x, y, wall.x, wall.b2) + shortestPath(wall.x, wall.b2, wallIndex + 1));
    }

    return minDist;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf %lf %lf", &walls[i].x, &walls[i].a1, &walls[i].b1, &walls[i].a2, &walls[i].b2);
    }

    double result = shortestPath(0, 5, 0);
    printf("%.2f\n", result);

    return 0;
}