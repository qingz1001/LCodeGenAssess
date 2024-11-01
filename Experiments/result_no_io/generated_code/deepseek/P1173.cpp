#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_C 100000

typedef struct {
    int x, y;
} Point;

int cmp(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x != p2->x) return p1->x - p2->x;
    return p1->y - p2->y;
}

bool is_adjacent(Point a, Point b) {
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
                printf("0\n");
            } else {
                printf("1\n");
            }
            continue;
        }

        qsort(crickets, c, sizeof(Point), cmp);

        bool connected = false;
        for (int i = 1; i < c; i++) {
            if (is_adjacent(crickets[i-1], crickets[i])) {
                connected = true;
                break;
            }
        }

        if (connected) {
            printf("1\n");
        } else {
            printf("-1\n");
        }
    }
    return 0;
}