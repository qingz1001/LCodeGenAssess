#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

typedef struct {
    long long x, y;
    char color;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->y != p2->y)
        return p1->y - p2->y;
    else
        return p1->x - p2->x;
}

int main() {
    int N;
    scanf("%d", &N);
    Point points[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%lld %lld %c", &points[i].x, &points[i].y, &points[i].color);
    }

    qsort(points, N, sizeof(Point), compare);

    int max_red_points = 0;
    for (int i = 0; i < N; i++) {
        int red_count = 0;
        for (int j = i + 1; j < N; j++) {
            if (points[j].y > points[i].y && points[j].y < points[i].y + 1) {
                if (points[j].color == 'R')
                    red_count++;
            } else {
                break;
            }
        }
        max_red_points = (red_count > max_red_points) ? red_count : max_red_points;
    }

    printf("%d\n", max_red_points);
    return 0;
}