#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-9

typedef struct {
    int id;
    double pos;
} Circle;

int compare(const void *a, const void *b) {
    return ((Circle *)a)->pos - ((Circle *)b)->pos > EPS ? 1 : -1;
}

double areaOfIntersection(Circle c1, Circle c2) {
    if (fabs(c1.pos - c2.pos) >= c1.r + c2.r)
        return 0;
    double d = fabs(c1.pos - c2.pos);
    double a1 = acos((d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d * c1.r));
    double a2 = acos((d * d + c2.r * c2.r - c1.r * c1.r) / (2 * d * c2.r));
    double h1 = c1.r * sin(a1);
    double h2 = c2.r * sin(a2);
    return 0.5 * c1.r * c1.r * a1 - h1 * d + 0.5 * c2.r * c2.r * a2 - h2 * d;
}

void findBestK(int n, int k, int r, int L, int *positions, int *result) {
    Circle circles[n];
    for (int i = 0; i < n; i++) {
        circles[i].id = i + 1;
        circles[i].pos = positions[i];
    }
    qsort(circles, n, sizeof(Circle), compare);

    double maxArea = 0;
    for (int i = 0; i <= n - k; i++) {
        double area = 0;
        for (int j = i; j < i + k; j++) {
            area += areaOfIntersection(circles[j], circles[(j + 1) % n]);
        }
        if (area > maxArea) {
            maxArea = area;
            for (int j = i; j < i + k; j++) {
                result[j - i] = circles[j].id;
            }
        }
    }
}

int main() {
    int n, k, r, L;
    scanf("%d %d %d %d", &n, &k, &r, &L);
    int positions[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &positions[i]);
    }

    int result[k];
    findBestK(n, k, r, L, positions, result);

    for (int i = 0; i < k; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}