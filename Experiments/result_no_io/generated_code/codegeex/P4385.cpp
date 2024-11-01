#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
    char color;
} Point;

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x == p2->x) return p1->y - p2->y;
    return p1->x - p2->x;
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %c", &points[i].x, &points[i].y, &points[i].color);
    }

    qsort(points, n, sizeof(Point), compare);

    int maxRedPoints = 0;
    for (int i = 0; i < n; i++) {
        if (points[i].color == 'B') continue;

        int redPointsLeft = 0, redPointsRight = 0;
        int j = i + 1;
        while (j < n && points[j].x == points[i].x) {
            if (points[j].color == 'R') redPointsRight++;
            j++;
        }

        j = i - 1;
        while (j >= 0 && points[j].x == points[i].x) {
            if (points[j].color == 'R') redPointsLeft++;
            j--;
        }

        maxRedPoints = (maxRedPoints > redPointsLeft + redPointsRight) ? maxRedPoints : (redPointsLeft + redPointsRight);
    }

    printf("%d\n", maxRedPoints);
    return 0;
}