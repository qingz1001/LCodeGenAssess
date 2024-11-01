#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return (p1->x + p1->y) - (p2->x + p2->y);
}

int main() {
    int n, x0, y0;
    scanf("%d %d %d", &n, &x0, &y0);

    Point *haystacks = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &haystacks[i].x, &haystacks[i].y);
    }

    qsort(haystacks, n, sizeof(Point), compare);

    int moves = 0;
    int current_x = x0, current_y = y0;

    for (int i = 0; i < n; i++) {
        if (haystacks[i].x >= current_x && haystacks[i].y >= current_y) {
            moves++;
            current_x = haystacks[i].x;
            current_y = haystacks[i].y;
        }
    }

    printf("%d\n", moves);

    free(haystacks);
    return 0;
}