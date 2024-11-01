#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int x;
    int y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x != p2->x) return p1->x - p2->x;
    return p1->y - p2->y;
}

int main() {
    int N;
    scanf("%d", &N);
    Point points[N];

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, N, sizeof(Point), compare);

    int minDiff = INT_MAX;
    for (int i = 0; i < N; i++) {
        int minDist = INT_MAX;
        int maxDist = 0;

        for (int j = 0; j < N; j++) {
            if (i != j) {
                int dist = (points[i].x - points[j].x) * (points[i].x - points[j].x) + (points[i].y - points[j].y) * (points[i].y - points[j].y);
                minDist = (dist < minDist) ? dist : minDist;
                maxDist = (dist > maxDist) ? dist : maxDist;
            }
        }

        int diff = maxDist - minDist;
        if (diff < minDiff) {
            minDiff = diff;
        }
    }

    printf("%d\n", minDiff);
    return 0;
}