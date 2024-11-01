#include <stdio.h>
#include <stdlib.h>

#define MAX_N 16
#define MAX_COLOR 20

typedef struct {
    int x1, y1, x2, y2, color;
} Rectangle;

Rectangle rectangles[MAX_N];
int n;
int color_count[MAX_COLOR + 1];
int visited[MAX_N];

int compare(const void *a, const void *b) {
    Rectangle *rectA = (Rectangle *)a;
    Rectangle *rectB = (Rectangle *)b;
    return rectA->y1 - rectB->y1;
}

int can_paint(int index) {
    for (int i = 0; i < n; i++) {
        if (!visited[i] && rectangles[i].y2 <= rectangles[index].y1 && rectangles[i].x2 > rectangles[index].x1 && rectangles[i].x1 < rectangles[index].x2) {
            return 0;
        }
    }
    return 1;
}

int min_brushes(int index) {
    if (index == n) return 0;

    int min_brushes_count = n;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && can_paint(i)) {
            visited[i] = 1;
            int current_color = rectangles[i].color;
            color_count[current_color]++;

            int additional_brushes = (color_count[current_color] == 1) ? 1 : 0;
            int result = additional_brushes + min_brushes(index + 1);
            if (result < min_brushes_count) {
                min_brushes_count = result;
            }

            color_count[current_color]--;
            visited[i] = 0;
        }
    }
    return min_brushes_count;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d %d", &rectangles[i].y1, &rectangles[i].x1, &rectangles[i].y2, &rectangles[i].x2, &rectangles[i].color);
    }

    qsort(rectangles, n, sizeof(Rectangle), compare);

    printf("%d\n", min_brushes(0));

    return 0;
}