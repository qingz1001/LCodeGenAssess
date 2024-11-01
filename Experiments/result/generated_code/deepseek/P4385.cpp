#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
    char color;
} Point;

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    Point points[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %c", &points[i].x, &points[i].y, &points[i].color);
    }

    int maxRedPoints = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (points[i].color == 'B' || points[j].color == 'B') continue;

            int redCount = 0;
            int dx = points[j].x - points[i].x;
            int dy = points[j].y - points[i].y;

            for (int k = 0; k < N; k++) {
                if (points[k].color == 'R') {
                    int cross = (points[k].x - points[i].x) * dy - (points[k].y - points[i].y) * dx;
                    if (cross == 0) {
                        redCount++;
                    }
                }
            }

            maxRedPoints = max(maxRedPoints, redCount);
        }
    }

    printf("%d\n", maxRedPoints);
    return 0;
}