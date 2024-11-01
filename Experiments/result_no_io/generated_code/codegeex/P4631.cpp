#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    double x, y, r;
    int id;
} Circle;

Circle circles[300005];
int n;

int compare(const void *a, const void *b) {
    Circle *circleA = (Circle *)a;
    Circle *circleB = (Circle *)b;
    if (circleA->r == circleB->r) return circleA->id - circleB->id;
    return circleB->r - circleA->r;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &circles[i].x, &circles[i].y, &circles[i].r);
        circles[i].id = i;
    }

    qsort(circles, n, sizeof(Circle), compare);

    int result[300005];
    memset(result, -1, sizeof(result));

    for (int i = 0; i < n; i++) {
        double maxR = circles[i].r;
        int maxId = circles[i].id;
        for (int j = i + 1; j < n; j++) {
            if (circles[j].r < maxR) break;
            double dx = circles[i].x - circles[j].x;
            double dy = circles[i].y - circles[j].y;
            double distance = sqrt(dx * dx + dy * dy);
            if (distance <= circles[i].r + circles[j].r) {
                result[circles[j].id] = circles[i].id;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}