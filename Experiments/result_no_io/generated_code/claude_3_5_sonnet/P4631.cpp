#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 300005

typedef struct {
    int x, y, r, id;
} Circle;

Circle circles[MAX_N];
int result[MAX_N];
int n;

int cmp(const void *a, const void *b) {
    Circle *c1 = (Circle *)a;
    Circle *c2 = (Circle *)b;
    if (c1->r != c2->r) return c2->r - c1->r;
    return c1->id - c2->id;
}

int intersect(Circle *c1, Circle *c2) {
    long long dx = c1->x - c2->x;
    long long dy = c1->y - c2->y;
    long long d2 = dx * dx + dy * dy;
    long long r_sum = (long long)(c1->r + c2->r) * (c1->r + c2->r);
    return d2 <= r_sum;
}

void solve() {
    qsort(circles, n, sizeof(Circle), cmp);

    for (int i = 0; i < n; i++) {
        if (result[circles[i].id] == 0) {
            result[circles[i].id] = circles[i].id;
            for (int j = i + 1; j < n; j++) {
                if (result[circles[j].id] == 0 && intersect(&circles[i], &circles[j])) {
                    result[circles[j].id] = circles[i].id;
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &circles[i].x, &circles[i].y, &circles[i].r);
        circles[i].id = i + 1;
    }

    solve();

    for (int i = 1; i <= n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}