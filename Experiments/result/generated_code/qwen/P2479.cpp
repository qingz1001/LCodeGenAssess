#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x != p2->x) return p1->x - p2->x;
    else return p1->y - p2->y;
}

int main() {
    int N;
    scanf("%d", &N);
    Point points[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, N, sizeof(Point), compare);

    int min_diff = INT_MAX;
    for (int i = 0; i < N; i++) {
        int max_dist = 0;
        int min_dist = INT_MAX;
        for (int j = 0; j < N; j++) {
            if (j == i) continue;
            int dist = abs(points[i].x - points[j].x) + abs(points[i].y - points[j].y);
            if (dist > max_dist) max_dist = dist;
            if (dist < min_dist) min_dist = dist;
        }
        if (max_dist - min_dist < min_diff) min_diff = max_dist - min_dist;
    }

    printf("%d\n", min_diff);
    return 0;
}