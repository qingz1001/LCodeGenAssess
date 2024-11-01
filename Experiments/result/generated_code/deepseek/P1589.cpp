#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Segment;

int compare(const void *a, const void *b) {
    Segment *segA = (Segment *)a;
    Segment *segB = (Segment *)b;
    return segA->start - segB->start;
}

int main() {
    int n, L;
    scanf("%d %d", &n, &L);

    Segment *segments = (Segment *)malloc(n * sizeof(Segment));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &segments[i].start, &segments[i].end);
    }

    qsort(segments, n, sizeof(Segment), compare);

    int boards = 0;
    int current_end = 0;

    for (int i = 0; i < n; i++) {
        if (segments[i].start > current_end) {
            current_end = segments[i].start;
        }

        while (current_end < segments[i].end) {
            current_end += L;
            boards++;
        }
    }

    printf("%d\n", boards);

    free(segments);
    return 0;
}