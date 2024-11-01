#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Tower;

int compareTowers(const void *a, const void *b) {
    Tower *t1 = (Tower *)a;
    Tower *t2 = (Tower *)b;
    return t1->x - t2->x;
}

double calculateRadius(Tower *towers, int m) {
    double maxRadius = 0.0;
    for (int i = 0; i < m - 1; i++) {
        double dx = towers[i + 1].x - towers[i].x;
        double dy = towers[i + 1].y + towers[i].y;
        double radius = sqrt(dx * dx + dy * dy) / 2.0;
        if (radius > maxRadius) {
            maxRadius = radius;
        }
    }
    return maxRadius;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Tower towers[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &towers[i].x, &towers[i].y);
    }

    qsort(towers, m, sizeof(Tower), compareTowers);

    double minRadius = calculateRadius(towers, m);
    printf("%.2f\n", minRadius);

    return 0;
}