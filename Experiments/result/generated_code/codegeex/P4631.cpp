#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 300005

typedef struct {
    double x, y, r;
    int id;
} Circle;

Circle circles[MAXN];
int n;
int result[MAXN];

int compare(const void *a, const void *b) {
    Circle *circleA = (Circle *)a;
    Circle *circleB = (Circle *)b;
    if (circleA->r == circleB->r) {
        return circleA->id - circleB->id;
    }
    return circleB->r - circleA->r;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &circles[i].x, &circles[i].y, &circles[i].r);
        circles[i].id = i;
    }

    qsort(circles, n, sizeof(Circle), compare);

    for (int i = 0; i < n; i++) {
        double maxRadius = circles[i].r;
        int maxIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (circles[j].r < maxRadius) break;
            double distance = sqrt((circles[i].x - circles[j].x) * (circles[i].x - circles[j].x) +
                                   (circles[i].y - circles[j].y) * (circles[i].y - circles[j].y));
            if (distance <= circles[i].r + circles[j].r) {
                maxRadius = circles[j].r;
                maxIndex = j;
            }
        }
        result[circles[i].id] = circles[maxIndex].id;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", result[i] + 1);
    }
    printf("\n");

    return 0;
}