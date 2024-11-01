#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100000

typedef struct {
    int x, y;
} Point;

int dist2(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int compare(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int main() {
    Point sys1, sys2;
    int N;
    Point missiles[MAXN];
    int dist1[MAXN], dist2[MAXN];

    scanf("%d %d %d %d", &sys1.x, &sys1.y, &sys2.x, &sys2.y);
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &missiles[i].x, &missiles[i].y);
        dist1[i] = dist2(sys1, missiles[i]);
        dist2[i] = dist2(sys2, missiles[i]);
    }

    qsort(dist1, N, sizeof(int), compare);
    qsort(dist2, N, sizeof(int), compare);

    int min_cost = dist1[0] + dist2[0];
    for (int i = 0; i < N; i++) {
        int cost = dist1[i];
        if (i < N - 1) cost += dist2[i + 1];
        if (cost < min_cost) min_cost = cost;
    }

    printf("%d\n", min_cost);

    return 0;
}