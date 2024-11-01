#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 6
#define PI 3.141592653589793

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return p1->x - p2->x;
}

double calculateArea(int N, Point points[], int boxX, int boxY, int boxXP, int boxYP) {
    double area = (boxXP - boxX) * (boxYP - boxY);
    for (int i = 0; i < N; i++) {
        int minX = fmax(points[i].x - 1, boxX);
        int maxX = fmin(points[i].x + 1, boxXP);
        int minY = fmax(points[i].y - 1, boxY);
        int maxY = fmin(points[i].y + 1, boxYP);
        area -= (maxX - minX) * (maxY - minY);
    }
    return area;
}

int main() {
    int N;
    scanf("%d", &N);
    int boxX, boxY, boxXP, boxYP;
    scanf("%d %d %d %d", &boxX, &boxY, &boxXP, &boxYP);

    Point points[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, N, sizeof(Point), compare);

    double minArea = calculateArea(N, points, boxX, boxY, boxXP, boxYP);
    printf("%.0f\n", round(minArea));

    return 0;
}