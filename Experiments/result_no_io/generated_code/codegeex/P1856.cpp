#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int x1, y1, x2, y2;
} Rectangle;

int compare(const void *a, const void *b) {
    Rectangle *rectA = (Rectangle *)a;
    Rectangle *rectB = (Rectangle *)b;
    if (rectA->x1 == rectB->x1) {
        return rectA->y1 - rectB->y1;
    }
    return rectA->x1 - rectB->x1;
}

int main() {
    int N;
    scanf("%d", &N);
    Rectangle rectangles[N];
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d%d", &rectangles[i].x1, &rectangles[i].y1, &rectangles[i].x2, &rectangles[i].y2);
    }

    qsort(rectangles, N, sizeof(Rectangle), compare);

    int x = INT_MIN, y = INT_MIN;
    int totalPerimeter = 0;
    for (int i = 0; i < N; i++) {
        if (rectangles[i].x1 > x) {
            totalPerimeter += 2 * (rectangles[i].x1 - x);
        }
        if (rectangles[i].y1 > y) {
            totalPerimeter += 2 * (rectangles[i].y1 - y);
        }
        if (rectangles[i].x2 > x) {
            totalPerimeter += 2 * (rectangles[i].x2 - x);
        }
        if (rectangles[i].y2 > y) {
            totalPerimeter += 2 * (rectangles[i].y2 - y);
        }
        x = rectangles[i].x2;
        y = rectangles[i].y2;
    }

    printf("%d\n", totalPerimeter);
    return 0;
}