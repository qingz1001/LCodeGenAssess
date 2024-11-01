#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 300005

typedef struct {
    int x, y, r, id;
} Circle;

Circle circles[MAXN];
int result[MAXN];
int n;

int cmp(const void *a, const void *b) {
    Circle *ca = (Circle *)a;
    Circle *cb = (Circle *)b;
    if (ca->r != cb->r) return cb->r - ca->r;
    return ca->id - cb->id;
}

int intersect(Circle *a, Circle *b) {
    long long dx = a->x - b->x;
    long long dy = a->y - b->y;
    long long dist_sq = dx * dx + dy * dy;
    long long sum_r = (long long)(a->r + b->r) * (a->r + b->r);
    return dist_sq <= sum_r;
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