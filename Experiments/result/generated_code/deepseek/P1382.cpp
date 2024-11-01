#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int height;
    int left;
    int right;
} Building;

typedef struct {
    int x;
    int y;
} Point;

int compareBuildings(const void *a, const void *b) {
    return ((Building *)a)->left - ((Building *)b)->left;
}

int main() {
    int n;
    scanf("%d", &n);

    Building *buildings = (Building *)malloc(n * sizeof(Building));
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &buildings[i].height, &buildings[i].left, &buildings[i].right);
    }

    qsort(buildings, n, sizeof(Building), compareBuildings);

    Point *points = (Point *)malloc((2 * n + 1) * sizeof(Point));
    int pointCount = 0;

    int currentHeight = 0;
    int currentX = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (buildings[i].left > currentX) {
            if (currentX != INT_MIN) {
                points[pointCount].x = currentX;
                points[pointCount].y = 0;
                pointCount++;
            }
            points[pointCount].x = buildings[i].left;
            points[pointCount].y = currentHeight;
            pointCount++;
            currentX = buildings[i].left;
        }

        if (buildings[i].height > currentHeight) {
            points[pointCount].x = buildings[i].left;
            points[pointCount].y = buildings[i].height;
            pointCount++;
            currentHeight = buildings[i].height;
        }

        while (i < n - 1 && buildings[i + 1].left < buildings[i].right) {
            i++;
            if (buildings[i].height > currentHeight) {
                points[pointCount].x = buildings[i].left;
                points[pointCount].y = buildings[i].height;
                pointCount++;
                currentHeight = buildings[i].height;
            }
        }

        points[pointCount].x = buildings[i].right;
        points[pointCount].y = currentHeight;
        pointCount++;
        currentHeight = 0;
        currentX = buildings[i].right;
    }

    points[pointCount].x = currentX;
    points[pointCount].y = 0;
    pointCount++;

    printf("%d\n", pointCount);
    for (int i = 0; i < pointCount; i++) {
        printf("%d %d\n", points[i].x, points[i].y);
    }

    free(buildings);
    free(points);

    return 0;
}