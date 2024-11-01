#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
    int x;
    int y;
    char color;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->y != p2->y) return p1->y - p2->y;
    return p1->x - p2->x;
}

int main() {
    int N;
    scanf("%d", &N);
    Point points[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %c", &points[i].x, &points[i].y, &points[i].color);
    }

    qsort(points, N, sizeof(Point), compare);

    int max_red_points = 0;
    for (int i = 0; i < N; i++) {
        int red_count = 0;
        for (int j = 0; j < N; j++) {
            if (i != j && points[i].y == points[j].y && points[i].color == 'R' && points[j].color == 'R') {
                red_count++;
            }
        }
        if (red_count > max_red_points) {
            max_red_points = red_count;
        }
    }

    printf("%d\n", max_red_points);

    return 0;
}