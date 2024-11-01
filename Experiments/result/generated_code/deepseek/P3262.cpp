#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10
#define MAXM 512
#define MAX_CONTRIB 2000

int n, m;
int w[MAXM][MAXN], f[MAXM][MAXN];
int dp[MAXM][MAXM];

void dfs(int node, int depth, int war_count, int total_contrib) {
    if (depth == n) {
        dp[node][war_count] = total_contrib;
        return;
    }

    int left_child = node * 2;
    int right_child = node * 2 + 1;

    // Left child goes to war
    dfs(left_child, depth + 1, war_count + 1, total_contrib + w[left_child][depth]);
    // Right child goes to war
    dfs(right_child, depth + 1, war_count + 1, total_contrib + w[right_child][depth]);

    // Left child goes to farming
    dfs(left_child, depth + 1, war_count, total_contrib + f[left_child][depth]);
    // Right child goes to farming
    dfs(right_child, depth + 1, war_count, total_contrib + f[right_child][depth]);
}

int main() {
    scanf("%d %d", &n, &m);

    int leaf_count = 1 << (n - 1);
    for (int i = 0; i < leaf_count; i++) {
        for (int j = 0; j < n - 1; j++) {
            scanf("%d", &w[leaf_count + i][j]);
        }
    }
    for (int i = 0; i < leaf_count; i++) {
        for (int j = 0; j < n - 1; j++) {
            scanf("%d", &f[leaf_count + i][j]);
        }
    }

    memset(dp, -1, sizeof(dp));
    dfs(1, 0, 0, 0);

    int max_contrib = 0;
    for (int i = 0; i <= m; i++) {
        if (dp[1][i] > max_contrib) {
            max_contrib = dp[1][i];
        }
    }

    printf("%d\n", max_contrib);

    return 0;
}