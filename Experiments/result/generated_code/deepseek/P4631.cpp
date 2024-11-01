#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y, r, id;
} Circle;

int compareCircles(const void *a, const void *b) {
    Circle *c1 = (Circle *)a;
    Circle *c2 = (Circle *)b;
    if (c1->r != c2->r) return c2->r - c1->r;
    return c1->id - c2->id;
}

int intersects(Circle c1, Circle c2) {
    long long dx = c1.x - c2.x;
    long long dy = c1.y - c2.y;
    long long dr = c1.r + c2.r;
    return dx * dx + dy * dy <= dr * dr;
}

int main() {
    int n;
    scanf("%d", &n);
    Circle circles[n];
    int result[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &circles[i].x, &circles[i].y, &circles[i].r);
        circles[i].id = i;
    }

    qsort(circles, n, sizeof(Circle), compareCircles);

    for (int i = 0; i < n; i++) {
        if (result[circles[i].id] != 0) continue;
        result[circles[i].id] = circles[i].id + 1;
        for (int j = i + 1; j < n; j++) {
            if (result[circles[j].id] == 0 && intersects(circles[i], circles[j])) {
                result[circles[j].id] = circles[i].id + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}