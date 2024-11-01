#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 19940417

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return p1->x - p2->x;
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    Point *points = (Point *)malloc(sizeof(Point) * K);
    for (int i = 0; i < K; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    qsort(points, K, sizeof(Point), compare);

    int count = 0;
    int max_height = 0;
    int current_height = 0;

    for (int i = 0; i < K; i++) {
        if (points[i].y < current_height) {
            current_height = points[i].y;
        } else {
            count++;
            current_height = points[i].y;
            max_height = current_height > max_height ? current_height : max_height;
        }
    }

    printf("%d %d\n", count % MOD, max_height);

    free(points);
    return 0;
}