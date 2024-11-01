#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x, y, w;
} Hole;

int compare(const void *a, const void *b) {
    Hole *holeA = (Hole *)a;
    Hole *holeB = (Hole *)b;
    if (holeA->x == holeB->x) {
        return holeA->y - holeB->y;
    }
    return holeA->x - holeB->x;
}

int main() {
    int n;
    scanf("%d", &n);
    Hole holes[n];

    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &holes[i].x, &holes[i].y, &holes[i].w);
    }

    qsort(holes, n, sizeof(Hole), compare);

    double totalWeight = 0;
    double xSum = 0, ySum = 0;

    for (int i = 0; i < n; i++) {
        totalWeight += holes[i].w;
        xSum += holes[i].w * holes[i].x;
        ySum += holes[i].w * holes[i].y;
    }

    double equilibriumX = xSum / totalWeight;
    double equilibriumY = ySum / totalWeight;

    printf("%.3lf %.3lf\n", equilibriumX, equilibriumY);

    return 0;
}