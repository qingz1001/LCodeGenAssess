#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 16
#define MAX_COLOR 20

typedef struct {
    int x1, y1, x2, y2, color;
} Rectangle;

Rectangle rectangles[MAX_N];
int N;
int color_count[MAX_COLOR + 1];
int visited[MAX_N];
int min_brush_count = MAX_N;

int compare_rectangles(const void *a, const void *b) {
    Rectangle *rectA = (Rectangle *)a;
    Rectangle *rectB = (Rectangle *)b;
    return rectA->y1 - rectB->y1;
}

void dfs(int index, int brush_count) {
    if (index == N) {
        if (brush_count < min_brush_count) {
            min_brush_count = brush_count;
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            int can_paint = 1;
            for (int j = 0; j < N; j++) {
                if (!visited[j] && rectangles[j].y1 < rectangles[i].y1 && rectangles[j].y2 > rectangles[i].y1) {
                    can_paint = 0;
                    break;
                }
            }

            if (can_paint) {
                visited[i] = 1;
                int new_brush_count = brush_count;
                if (color_count[rectangles[i].color] == 0) {
                    new_brush_count++;
                }
                color_count[rectangles[i].color]++;

                dfs(index + 1, new_brush_count);

                color_count[rectangles[i].color]--;
                visited[i] = 0;
            }
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d %d", &rectangles[i].y1, &rectangles[i].x1, &rectangles[i].y2, &rectangles[i].x2, &rectangles[i].color);
    }

    qsort(rectangles, N, sizeof(Rectangle), compare_rectangles);

    dfs(0, 0);

    printf("%d\n", min_brush_count);

    return 0;
}