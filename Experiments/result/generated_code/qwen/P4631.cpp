#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int x, y, r;
} Circle;

int compare(const void *a, const void *b) {
    Circle *circleA = (Circle *)a;
    Circle *circleB = (Circle *)b;
    if (circleA->r != circleB->r) return circleB->r - circleA->r;
    return circleA->x - circleB->x;
}

void findAndRemove(Circle circles[], int n, int result[]) {
    while (n > 0) {
        qsort(circles, n, sizeof(Circle), compare);
        int maxIndex = 0;
        for (int i = 1; i < n; i++) {
            if (circles[i].x + circles[i].r <= circles[maxIndex].x - circles[maxIndex].r ||
                circles[i].x - circles[i].r >= circles[maxIndex].x + circles[maxIndex].r ||
                circles[i].y + circles[i].r <= circles[maxIndex].y - circles[maxIndex].r ||
                circles[i].y - circles[i].r >= circles[maxIndex].y + circles[maxIndex].r) {
                continue;
            }
            double d = sqrt((circles[i].x - circles[maxIndex].x) * (circles[i].x - circles[maxIndex].x) +
                            (circles[i].y - circles[maxIndex].y) * (circles[i].y - circles[maxIndex].y));
            if (d <= circles[i].r + circles[maxIndex].r) {
                maxIndex = i;
            }
        }
        result[maxIndex] = -1;
        for (int i = 0; i < n; i++) {
            if (i == maxIndex) continue;
            double d = sqrt((circles[i].x - circles[maxIndex].x) * (circles[i].x - circles[maxIndex].x) +
                            (circles[i].y - circles[maxIndex].y) * (circles[i].y - circles[maxIndex].y));
            if (d <= circles[i].r + circles[maxIndex].r) {
                circles[i].x = -1;
                circles[i].y = -1;
                circles[i].r = -1;
                n--;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Circle circles[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &circles[i].x, &circles[i].y, &circles[i].r);
    }
    int result[MAXN];
    findAndRemove(circles, n, result);
    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}