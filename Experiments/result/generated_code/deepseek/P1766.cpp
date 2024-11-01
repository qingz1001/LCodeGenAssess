#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x1, y1, x2, y2;
} Segment;

int compare(const void *a, const void *b) {
    Segment *s1 = (Segment *)a;
    Segment *s2 = (Segment *)b;
    return s1->y1 - s2->y1;
}

int main() {
    int N, S;
    scanf("%d %d", &N, &S);

    Segment segments[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
    }

    // Sort segments by their y1 value in ascending order
    qsort(segments, N, sizeof(Segment), compare);

    int current_x = S;
    int current_y = 0;

    for (int i = 0; i < N; i++) {
        if (segments[i].x1 <= current_x && current_x <= segments[i].x2 && segments[i].y1 > current_y) {
            current_y = segments[i].y1;
            if (segments[i].y1 > segments[i].y2) {
                current_x = segments[i].x2;
            } else {
                current_x = segments[i].x1;
            }
        }
    }

    printf("%d\n", current_x);

    return 0;
}