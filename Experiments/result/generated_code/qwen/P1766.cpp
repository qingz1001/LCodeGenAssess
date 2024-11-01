#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

typedef struct {
    int x1, y1, x2, y2;
} Segment;

int compare(const void *a, const void *b) {
    Segment *segA = (Segment *)a;
    Segment *segB = (Segment *)b;
    if (segA->y1 != segB->y1) return segA->y1 - segB->y1;
    return segA->x1 - segB->x1;
}

int main() {
    int N, S;
    scanf("%d %d", &N, &S);
    Segment segments[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
    }

    qsort(segments, N, sizeof(Segment), compare);

    int result = S;
    for (int i = 0; i < N; i++) {
        if (result >= segments[i].x1 && result <= segments[i].x2) {
            if (segments[i].y1 > segments[i].y2) {
                result = segments[i].x2;
            } else {
                result = segments[i].x1;
            }
        }
    }

    printf("%d\n", result);
    return 0;
}