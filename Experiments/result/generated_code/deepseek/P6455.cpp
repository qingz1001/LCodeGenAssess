#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100005

typedef struct {
    int index;
    double pos;
} Circle;

int compareCircles(const void *a, const void *b) {
    Circle *circleA = (Circle *)a;
    Circle *circleB = (Circle *)b;
    if (circleA->pos < circleB->pos) return -1;
    if (circleA->pos > circleB->pos) return 1;
    return 0;
}

int main() {
    int n, k, r, L;
    scanf("%d %d %d %d", &n, &k, &r, &L);
    Circle circles[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%lf", &circles[i].pos);
        circles[i].index = i + 1;
    }

    qsort(circles, n, sizeof(Circle), compareCircles);

    int selected[MAXN];
    for (int i = 0; i < k; i++) {
        selected[i] = circles[i].index;
    }

    qsort(selected, k, sizeof(int), compareCircles);

    for (int i = 0; i < k; i++) {
        printf("%d ", selected[i]);
    }
    printf("\n");

    return 0;
}