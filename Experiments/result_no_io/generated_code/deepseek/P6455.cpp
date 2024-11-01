#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100005
#define PI 3.14159265358979323846

typedef struct {
    int id;
    double pos;
} Circle;

int cmp(const void *a, const void *b) {
    Circle *ca = (Circle *)a;
    Circle *cb = (Circle *)b;
    if (ca->pos < cb->pos) return -1;
    if (ca->pos > cb->pos) return 1;
    return 0;
}

int main() {
    int n, k, r, L;
    scanf("%d %d %d %d", &n, &k, &r, &L);
    Circle circles[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%lf", &circles[i].pos);
        circles[i].id = i + 1;
    }

    qsort(circles, n, sizeof(Circle), cmp);

    double max_area = 0;
    int best_indices[MAXN];
    for (int i = 0; i < k; i++) {
        best_indices[i] = circles[i].id;
    }

    for (int i = 0; i <= n - k; i++) {
        double area = 0;
        for (int j = 0; j < k; j++) {
            int idx = (i + j) % n;
            double overlap = 0;
            for (int m = 0; m < j; m++) {
                int prev_idx = (i + m) % n;
                double dist = fabs(circles[idx].pos - circles[prev_idx].pos);
                if (dist > 2 * r) continue;
                double h = sqrt(r * r - (dist / 2) * (dist / 2));
                overlap += 2 * h;
            }
            area += PI * r * r - overlap;
        }
        if (area > max_area) {
            max_area = area;
            for (int j = 0; j < k; j++) {
                best_indices[j] = circles[(i + j) % n].id;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        printf("%d ", best_indices[i]);
    }
    printf("\n");

    return 0;
}