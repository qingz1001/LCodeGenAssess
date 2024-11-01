#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define EPS 1e-9

typedef struct {
    int id;
    double x;
} Circle;

int cmp(const void *a, const void *b) {
    return ((Circle *)a)->x < ((Circle *)b)->x ? -1 : 1;
}

double intersect(Circle a, Circle b) {
    if (fabs(a.x - b.x) > 2 * a.r + EPS)
        return 0;
    double d = fabs(a.x - b.x);
    double h = sqrt(a.r * a.r - (d / 2) * (d / 2));
    return 2 * h * (d / 2);
}

void solve(int n, int k, int r, int L, Circle circles[]) {
    qsort(circles, n, sizeof(Circle), cmp);

    double max_area = 0;
    for (int i = 0; i <= n - k; i++) {
        double area = 0;
        for (int j = i; j < i + k; j++) {
            for (int l = j + 1; l < i + k; l++) {
                area += intersect(circles[j], circles[l]);
            }
        }
        if (area > max_area) {
            max_area = area;
        }
    }

    printf("%.9f\n", max_area);
}

int main() {
    int n, k, r, L;
    scanf("%d %d %d %d", &n, &k, &r, &L);

    Circle circles[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &circles[i].id);
        circles[i].x = (circles[i].id - 1) * (double)L / n;
    }

    solve(n, k, r, L, circles);

    return 0;
}