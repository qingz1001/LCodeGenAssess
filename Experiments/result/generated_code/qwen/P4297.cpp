#include <stdio.h>
#include <stdlib.h>

#define MAX_N 11
#define INF 0x3f3f3f3f

int N;
int cost[MAX_N][MAX_N];
int change_cost[MAX_N * (1 << N)];
int dp[1 << MAX_N][2];

void dfs(int node, int parent, int mask) {
    if (node > (1 << N)) return;

    int left = node << 1;
    int right = left | 1;

    dfs(left, node, mask);
    dfs(right, node, mask);

    for (int i = 0; i < 2; i++) {
        dp[node][i] = INF;
        for (int j = 0; j < 2; j++) {
            dp[node][i] = fmin(dp[node][i], dp[left][j] + dp[right][i ^ j] + cost[node][left]);
        }
    }

    dp[node][mask & 1] = fmin(dp[node][mask & 1], dp[node][!(mask & 1)] + change_cost[node - 1]);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= (1 << N); i++) {
        scanf("%d", &cost[i][i]);
    }
    for (int i = 1; i <= (1 << N); i++) {
        scanf("%d", &change_cost[i - 1]);
    }
    for (int i = 0; i < (1 << N) - 1; i++) {
        for (int j = 0; j < (1 << N) - i; j++) {
            scanf("%d", &cost[j + 1][j + i + 1]);
        }
    }

    dfs(1, 0, 0);

    printf("%d\n", dp[1][0]);

    return 0;
}