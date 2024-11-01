#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001
#define MAXD 5

typedef struct {
    int coordinates[MAXD];
} Point;

int manhattanDistance(Point p1, Point p2, int d) {
    int distance = 0;
    for (int i = 0; i < d; i++) {
        distance += abs(p1.coordinates[i] - p2.coordinates[i]);
    }
    return distance;
}

int main() {
    int n, d;
    scanf("%d %d", &n, &d);

    Point points[MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            scanf("%d", &points[i].coordinates[j]);
        }
    }

    int maxDistance = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int distance = manhattanDistance(points[i], points[j], d);
            if (distance > maxDistance) {
                maxDistance = distance;
            }
        }
    }

    printf("%d\n", maxDistance);

    return 0;
}