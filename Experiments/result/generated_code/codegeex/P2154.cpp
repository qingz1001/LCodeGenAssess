#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 2147483648

typedef struct {
    int x, y;
} Point;

int cmp(const void *a, const void *b) {
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    if (p1->x != p2->x) return p1->x - p2->x;
    return p1->y - p2->y;
}

int main() {
    int N, M, W, k;
    scanf("%d %d %d", &N, &M, &W);
    Point trees[W];
    for (int i = 0; i < W; i++) {
        scanf("%d %d", &trees[i].x, &trees[i].y);
    }
    scanf("%d", &k);

    qsort(trees, W, sizeof(Point), cmp);

    long long ans = 0;
    for (int i = 0; i < W; i++) {
        int x = trees[i].x, y = trees[i].y;
        int count = 0;
        for (int j = 0; j < W; j++) {
            if (trees[j].x == x || trees[j].y == y) {
                count++;
            }
        }
        if (count >= 4 * k) {
            ans += count - 4 * k + 1;
        }
    }

    printf("%lld\n", ans % MOD);
    return 0;
}