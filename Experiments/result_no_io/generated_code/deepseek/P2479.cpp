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

    // Sort points by x coordinate
    qsort(points, N, sizeof(Point), compareX);

    // Calculate the minimum distance difference for x-axis
    int minDiffX = INT_MAX;
    for (int i = 1; i < N; i++) {
        minDiffX = min(minDiffX, points[i].x - points[i-1].x);
    }

    // Sort points by y coordinate
    qsort(points, N, sizeof(Point), compareY);

    // Calculate the minimum distance difference for y-axis
    int minDiffY = INT_MAX;
    for (int i = 1; i < N; i++) {
        minDiffY = min(minDiffY, points[i].y - points[i-1].y);
    }

    // The answer is the maximum of the two minimum differences
    int result = max(minDiffX, minDiffY);
    printf("%d\n", result);

    return 0;
}