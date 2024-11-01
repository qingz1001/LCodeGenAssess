#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;

int compareX(const void *a, const void *b) {
    return ((Point *)a)->x - ((Point *)b)->x;
}

int compareY(const void *a, const void *b) {
    return ((Point *)a)->y - ((Point *)b)->y;
}

int manhattanDistance(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    Point points[N];

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, N, sizeof(Point), compareX);
    int maxDistX = points[N-1].x - points[0].x;

    qsort(points, N, sizeof(Point), compareY);
    int maxDistY = points[N-1].y - points[0].y;

    int maxDist = max(maxDistX, maxDistY);

    int minDist = maxDist;

    for (int i = 0; i < N; i++) {
        int maxDistFromPoint = 0;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                int dist = manhattanDistance(points[i], points[j]);
                if (dist > maxDistFromPoint) {
                    maxDistFromPoint = dist;
                }
            }
        }
        minDist = min(minDist, maxDistFromPoint);
    }

    printf("%d\n", minDist);

    return 0;
}