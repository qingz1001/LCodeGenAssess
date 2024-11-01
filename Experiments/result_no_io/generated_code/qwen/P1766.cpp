#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x1, y1, x2, y2;
} Segment;

int main() {
    int N, S;
    scanf("%d %d", &N, &S);

    Segment *segments = (Segment *)malloc(N * sizeof(Segment));
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
    }

    int result = S;
    for (int i = 0; i < N; i++) {
        if ((segments[i].y1 - segments[i].y2) * (result - segments[i].x1) >= (segments[i].x1 - segments[i].x2) * (segments[i].y1 - result)) {
            result = segments[i].x1 + (segments[i].y1 - result) * (segments[i].x2 - segments[i].x1) / (segments[i].y2 - segments[i].y1);
        }
    }

    printf("%d\n", result);

    free(segments);
    return 0;
}