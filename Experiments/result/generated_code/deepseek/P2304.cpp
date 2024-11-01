#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define INF 0x3f3f3f3f

typedef struct {
    int x, y;
} Point;

Point trees[MAXN];
int n;
int dp[MAXN], pre[MAXN];

int cmp(const void *a, const void *b) {
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    if (pa->y == pb->y) return pa->x - pb->x;
    return pa->y - pb->y;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &trees[i].x, &trees[i].y);
    }

    qsort(trees + 1, n, sizeof(Point), cmp);

    memset(dp, 0, sizeof(dp));
    memset(pre, -1, sizeof(pre));

    int max_count = 0, max_index = 0;

    for (int i = 1; i <= n; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++) {
            if (trees[j].y < trees[i].y && abs(trees[j].x - trees[i].x) <= trees[i].y - trees[j].y) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    pre[i] = j;
                }
            }
        }
        if (dp[i] > max_count) {
            max_count = dp[i];
            max_index = i;
        }
    }

    printf("%d\n", max_count);

    int path[MAXN], path_len = 0;
    for (int i = max_index; i != -1; i = pre[i]) {
        path[path_len++] = i;
    }

    for (int i = path_len - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");

    int machines = 0;
    for (int i = 1; i <= n; i++) {
        if (trees[i].x != 0 && trees[i].y != 0) {
            machines++;
        }
    }

    printf("%d\n", machines);

    return 0;
}