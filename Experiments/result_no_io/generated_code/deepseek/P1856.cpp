#include <stdio.h>
#include <stdlib.h>

#define MAXN 5000
#define MAXCOORD 10000

typedef struct {
    int x1, y1, x2, y2;
} Rectangle;

Rectangle rects[MAXN];
int x_events[MAXN * 2];
int y_events[MAXN * 2];

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &rects[i].x1, &rects[i].y1, &rects[i].x2, &rects[i].y2);
        x_events[i * 2] = rects[i].x1;
        x_events[i * 2 + 1] = rects[i].x2;
        y_events[i * 2] = rects[i].y1;
        y_events[i * 2 + 1] = rects[i].y2;
    }

    qsort(x_events, N * 2, sizeof(int), compare);
    qsort(y_events, N * 2, sizeof(int), compare);

    int perimeter = 0;

    for (int i = 0; i < N * 2 - 1; i++) {
        for (int j = 0; j < N * 2 - 1; j++) {
            int x1 = x_events[i], x2 = x_events[i + 1];
            int y1 = y_events[j], y2 = y_events[j + 1];

            int count = 0;
            for (int k = 0; k < N; k++) {
                if (rects[k].x1 <= x1 && rects[k].x2 >= x2 && rects[k].y1 <= y1 && rects[k].y2 >= y2) {
                    count++;
                }
            }

            if (count > 0) {
                perimeter += (x2 - x1) + (y2 - y1);
            }
        }
    }

    printf("%d\n", perimeter * 2);

    return 0;
}