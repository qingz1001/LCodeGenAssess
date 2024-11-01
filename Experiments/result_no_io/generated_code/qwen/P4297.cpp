#include <stdio.h>
#include <stdlib.h>

#define MAX_N 11
#define INF 0x3f3f3f3f

int N;
int cost[MAX_N][MAX_N];
int change_cost[MAX_N];
int dp[MAX_N][MAX_N][2];

void dfs(int node, int parent, int left[], int right[]) {
    if (node > (1 << N)) return;

    int n = 1 << (N - __builtin_clz(node));
    for (int i = 0; i < n; i++) {
        if (node * 2 + i <= (1 << N)) left[node * 2 + i] += left[node];
        if (node * 2 + i + 1 <= (1 << N)) right[node * 2 + i + 1] += right[node];
    }

    dfs(node * 2, node, left, right);
    dfs(node * 2 + 1, node, left, right);

    if (node == 1) {
        for (int i = 1; i <= (1 << N); i++) {
            dp[1][i][0] = left[i];
            dp[1][i][1] = right[i];
        }
    } else {
        for (int i = 1; i <= (1 << N); i++) {
            dp[node][i][0] = dp[node * 2][i][0] + dp[node * 2 + 1][i][0];
            dp[node][i][1] = dp[node * 2][i][1] + dp[node * 2 + 1][i][1];
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= (1 << N); i++) {
        scanf("%d", &cost[i][i]);
    }
    for (int i = 1; i <= (1 << N); i++) {
        scanf("%d", &change_cost[i]);
    }
    for (int i = 0; i < (1 << N) - 1; i++) {
        for (int j = 1; j <= (1 << N); j++) {
            scanf("%d", &cost[j][j + i]);
        }
    }

    int left[(1 << N) + 1], right[(1 << N) + 1];
    for (int i = 1; i <= (1 << N); i++) {
        left[i] = right[i] = 0;
    }

    dfs(1, 0, left, right);

    int min_cost = INF;
    for (int i = 1; i <= (1 << N); i++) {
        min_cost = fmin(min_cost, dp[1][i][0] + dp[1][i][1]);
    }

    printf("%d\n", min_cost);

    return 0;
}