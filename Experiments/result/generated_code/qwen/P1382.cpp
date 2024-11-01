#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    long long x, y;
} Point;

int cmp(const void *a, const void *b) {
    return ((Point *)a)->x != ((Point *)b)->x ? ((Point *)a)->x - ((Point *)b)->x : ((Point *)a)->y - ((Point *)b)->y;
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[MAXN * 2];

    for (int i = 0; i < n; i++) {
        long long h, l, r;
        scanf("%lld %lld %lld", &h, &l, &r);
        points[i * 2] = (Point){l, h};
        points[i * 2 + 1] = (Point){r, -h};
    }

    qsort(points, n * 2, sizeof(Point), cmp);

    long long prev_x = 0, prev_y = 0;
    int m = 0;
    for (int i = 0; i < n * 2; i++) {
        if (points[i].y > 0 && prev_y == 0) {
            printf("0 0\n");
            m++;
        }
        if (prev_x != points[i].x || prev_y != points[i].y) {
            printf("%lld %lld\n", points[i].x, points[i].y);
            m++;
            prev_x = points[i].x;
            prev_y = points[i].y;
        }
    }
    if (prev_y != 0) {
        printf("0 0\n");
        m++;
    }

    printf("%d\n", m);
    return 0;
}