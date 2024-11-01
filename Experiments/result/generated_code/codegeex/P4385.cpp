#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

typedef struct {
    int x, y;
    char color;
} Point;

int cmp(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x != p2->x) {
        return p1->x - p2->x;
    } else {
        return p1->y - p2->y;
    }
}

int main() {
    int N;
    scanf("%d", &N);
    Point points[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %c", &points[i].x, &points[i].y, &points[i].color);
    }

    qsort(points, N, sizeof(Point), cmp);

    int maxRedPoints = 0;
    for (int i = 0; i < N; i++) {
        if (points[i].color == 'R') {
            int redPoints = 1;
            int j = i + 1;
            while (j < N && points[j].color == 'R') {
                redPoints++;
                j++;
            }
            maxRedPoints = (maxRedPoints > redPoints) ? maxRedPoints : redPoints;
            i = j - 1;
        }
    }

    printf("%d\n", maxRedPoints);
    return 0;
}