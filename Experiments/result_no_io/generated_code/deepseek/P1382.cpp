#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int h;
} Point;

int comparePoints(const void *a, const void *b) {
    return ((Point *)a)->x - ((Point *)b)->x;
}

int main() {
    int n;
    scanf("%d", &n);

    Point *points = (Point *)malloc(sizeof(Point) * n * 2);
    int pointCount = 0;

    for (int i = 0; i < n; i++) {
        int h, l, r;
        scanf("%d %d %d", &h, &l, &r);
        points[pointCount].x = l;
        points[pointCount].h = h;
        pointCount++;
        points[pointCount].x = r;
        points[pointCount].h = -h; // 使用负数表示右边界
        pointCount++;
    }

    qsort(points, pointCount, sizeof(Point), comparePoints);

    int *heights = (int *)malloc(sizeof(int) * pointCount);
    int heightCount = 0;

    int currentHeight = 0;
    int maxHeight = 0;

    for (int i = 0; i < pointCount; i++) {
        if (points[i].h > 0) {
            heights[heightCount++] = points[i].h;
            if (points[i].h > maxHeight) {
                maxHeight = points[i].h;
            }
        } else {
            for (int j = 0; j < heightCount; j++) {
                if (heights[j] == -points[i].h) {
                    heights[j] = 0;
                    break;
                }
            }
            maxHeight = 0;
            for (int j = 0; j < heightCount; j++) {
                if (heights[j] > maxHeight) {
                    maxHeight = heights[j];
                }
            }
        }

        if (maxHeight != currentHeight) {
            printf("%d %d\n", points[i].x, maxHeight);
            currentHeight = maxHeight;
        }
    }

    free(points);
    free(heights);

    return 0;
}