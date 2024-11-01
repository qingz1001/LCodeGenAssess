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
int dp[MAXN];
int prev[MAXN];
int up[MAXN], left_up[MAXN], right_up[MAXN];

int cmp(const void *a, const void *b) {
    Point *pa = (Point *)a;
    Point *pb = (Point *)b;
    if (pa->y == pb->y) return pa->x - pb->x;
    return pa->y - pb->y;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &trees[i].x, &trees[i].y);
    }

    qsort(trees, n, sizeof(Point), cmp);

    memset(dp, 0, sizeof(dp));
    memset(prev, -1, sizeof(prev));

    for (int i = 0; i < n; i++) {
        up[i] = left_up[i] = right_up[i] = -1;
        for (int j = i - 1; j >= 0; j--) {
            if (trees[j].y < trees[i].y && trees[j].x == trees[i].x) {
                if (up[i] == -1 || dp[j] > dp[up[i]]) {
                    up[i] = j;
                }
            }
            if (trees[j].y < trees[i].y && trees[j].x + trees[j].y == trees[i].x + trees[i].y) {
                if (left_up[i] == -1 || dp[j] > dp[left_up[i]]) {
                    left_up[i] = j;
                }
            }
            if (trees[j].y < trees[i].y && trees[j].x - trees[j].y == trees[i].x - trees[i].y) {
                if (right_up[i] == -1 || dp[j] > dp[right_up[i]]) {
                    right_up[i] = j;
                }
            }
        }

        int max_dp = 0, max_prev = -1;
        if (up[i] != -1 && dp[up[i]] > max_dp) {
            max_dp = dp[up[i]];
            max_prev = up[i];
        }
        if (left_up[i] != -1 && dp[left_up[i]] > max_dp) {
            max_dp = dp[left_up[i]];
            max_prev = left_up[i];
        }
        if (right_up[i] != -1 && dp[right_up[i]] > max_dp) {
            max_dp = dp[right_up[i]];
            max_prev = right_up[i];
        }

        dp[i] = max_dp + 1;
        prev[i] = max_prev;
    }

    int max_index = 0;
    for (int i = 1; i < n; i++) {
        if (dp[i] > dp[max_index]) {
            max_index = i;
        }
    }

    printf("%d\n", dp[max_index]);

    int path[MAXN], path_len = 0;
    for (int i = max_index; i != -1; i = prev[i]) {
        path[path_len++] = i;
    }

    for (int i = path_len - 1; i >= 0; i--) {
        printf("%d", path[i] + 1);
        if (i > 0) printf(" ");
    }
    printf("\n");

    int machine_count = 0;
    for (int i = 0; i < path_len; i++) {
        if (prev[path[i]] != -1 && (trees[prev[path[i]]].x != trees[path[i]].x)) {
            machine_count++;
        }
    }

    printf("%d\n", machine_count);

    return 0;
}