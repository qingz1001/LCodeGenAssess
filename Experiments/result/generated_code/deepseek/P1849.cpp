#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x == p2->x) return p1->y - p2->y;
    return p1->x - p2->x;
}

int main() {
    int n, x0, y0;
    scanf("%d %d %d", &n, &x0, &y0);
    Point *haystacks = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &haystacks[i].x, &haystacks[i].y);
    }

    qsort(haystacks, n, sizeof(Point), compare);

    int count = 0;
    int x = x0, y = y0;
    for (int i = 0; i < n; i++) {
        if (haystacks[i].x >= x && haystacks[i].y >= y) {
            count++;
            x = haystacks[i].x;
            y = haystacks[i].y;
        }
    }

    printf("%d\n", count);
    free(haystacks);
    return 0;
}