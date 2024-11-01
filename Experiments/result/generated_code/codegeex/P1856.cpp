#include <stdio.h>
#include <stdlib.h>

#define MAX_COORD 20001
#define OFFSET 10000

typedef struct {
    int x1, y1, x2, y2;
} Rectangle;

int compare(const void *a, const void *b) {
    Rectangle *rectA = (Rectangle *)a;
    Rectangle *rectB = (Rectangle *)b;
    if (rectA->x1 != rectB->x1) {
        return rectA->x1 - rectB->x1;
    } else {
        return rectA->y1 - rectB->y1;
    }
}

int main() {
    int N;
    scanf("%d", &N);

    Rectangle rectangles[N];
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d%d", &rectangles[i].x1, &rectangles[i].y1, &rectangles[i].x2, &rectangles[i].y2);
        rectangles[i].x1 += OFFSET;
        rectangles[i].x2 += OFFSET;
        rectangles[i].y1 += OFFSET;
        rectangles[i].y2 += OFFSET;
    }

    qsort(rectangles, N, sizeof(Rectangle), compare);

    int x = 0, y = 0;
    int x1 = 0, y1 = 0;
    int perimeter = 0;

    for (int i = 0; i < N; i++) {
        if (rectangles[i].x1 > x) {
            perimeter += 2 * (x - x1);
            x = rectangles[i].x1;
        }
        if (rectangles[i].x2 > x) {
            perimeter += 2 * (rectangles[i].x2 - x);
            x = rectangles[i].x2;
        }
        if (rectangles[i].y1 > y) {
            perimeter += 2 * (y - y1);
            y = rectangles[i].y1;
        }
        if (rectangles[i].y2 > y) {
            perimeter += 2 * (rectangles[i].y2 - y);
            y = rectangles[i].y2;
        }
        x1 = rectangles[i].x1;
        y1 = rectangles[i].y1;
    }

    perimeter += 2 * (x - x1) + 2 * (y - y1);

    printf("%d\n", perimeter);

    return 0;
}