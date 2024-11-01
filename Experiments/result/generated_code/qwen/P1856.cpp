#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000

typedef struct {
    int x1, y1;
    int x2, y2;
} Rectangle;

int main() {
    int N;
    scanf("%d", &N);

    Rectangle rectangles[MAX_N];
    for (int i = 0; i < N; ++i) {
        scanf("%d %d %d %d", &rectangles[i].x1, &rectangles[i].y1, &rectangles[i].x2, &rectangles[i].y2);
    }

    int maxX = -10000, minX = 10000, maxY = -10000, minY = 10000;

    for (int i = 0; i < N; ++i) {
        if (rectangles[i].x1 > maxX) maxX = rectangles[i].x1;
        if (rectangles[i].x2 < minX) minX = rectangles[i].x2;
        if (rectangles[i].y1 > maxY) maxY = rectangles[i].y1;
        if (rectangles[i].y2 < minY) minY = rectangles[i].y2;
    }

    int perimeter = 2 * ((maxX - minX) + (maxY - minY));

    printf("%d\n", perimeter);

    return 0;
}