#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_C 100000

typedef struct {
    int x, y;
} Point;

int comparePoints(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x != p2->x) return p1->x - p2->x;
    return p1->y - p2->y;
}

bool isAdjacent(Point a, Point b) {
    return (abs(a.x - b.x) + abs(a.y - b.y) == 1);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, c;
        scanf("%d %d %d", &n, &m, &c);
        Point crickets[MAX_C];
        for (int i = 0; i < c; i++) {
            scanf("%d %d", &crickets[i].x, &crickets[i].y);
        }

        if (c == 0) {
            if (n == 1 && m == 1) {
                printf("-1\n");
            } else {
                printf("0\n");
            }
            continue;
        }

        qsort(crickets, c, sizeof(Point), comparePoints);

        bool found = false;
        for (int i = 0; i < c; i++) {
            for (int j = i + 1; j < c; j++) {
                if (isAdjacent(crickets[i], crickets[j])) {
                    found = true;
                    break;
                }
            }
            if (found) break;
        }

        if (found) {
            printf("1\n");
        } else {
            if (c == 1) {
                printf("-1\n");
            } else {
                printf("2\n");
            }
        }
    }
    return 0;
}