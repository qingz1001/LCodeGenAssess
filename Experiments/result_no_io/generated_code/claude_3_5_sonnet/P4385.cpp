#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1000
#define EPS 1e-9

typedef struct {
    long long x, y;
    char color;
} Point;

Point points[MAX_N];
int N;

int cmp(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if (p1->x != p2->x) return p1->x - p2->x;
    return p1->y - p2->y;
}

int ccw(Point* a, Point* b, Point* c) {
    long long area = (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
    if (area > 0) return 1;
    if (area < 0) return -1;
    return 0;
}

int count_red_between(int i, int j) {
    int count = 0;
    for (int k = 0; k < N; k++) {
        if (k == i || k == j) continue;
        if (ccw(&points[i], &points[j], &points[k]) == 0) continue;
        if (points[k].color == 'R') count++;
    }
    return count;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld %c", &points[i].x, &points[i].y, &points[i].color);
    }

    qsort(points, N, sizeof(Point), cmp);

    int max_red = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (points[i].color == 'B' && points[j].color == 'B') continue;
            int red_count = count_red_between(i, j);
            if (red_count > max_red) max_red = red_count;
        }
    }

    printf("%d\n", max_red);
    return 0;
}