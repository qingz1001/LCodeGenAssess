#include <stdio.h>
#include <stdlib.h>

#define MAX_COORD 10001

typedef struct {
    int x1, y1, x2, y2;
} Rectangle;

int main() {
    int n;
    scanf("%d", &n);

    Rectangle rectangles[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &rectangles[i].x1, &rectangles[i].y1, &rectangles[i].x2, &rectangles[i].y2);
    }

    int area[MAX_COORD][MAX_COORD] = {0};

    for (int i = 0; i < n; i++) {
        for (int x = rectangles[i].x1; x < rectangles[i].x2; x++) {
            for (int y = rectangles[i].y1; y < rectangles[i].y2; y++) {
                area[x][y] = 1;
            }
        }
    }

    int totalArea = 0;
    for (int x = 0; x < MAX_COORD; x++) {
        for (int y = 0; y < MAX_COORD; y++) {
            if (area[x][y] == 1) {
                totalArea++;
            }
        }
    }

    printf("%d\n", totalArea);

    return 0;
}