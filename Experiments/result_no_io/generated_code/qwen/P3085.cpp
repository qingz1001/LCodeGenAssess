#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n;
int graph[MAXN][2];
int color[MAXN];
int dp[MAXN][2];

void dfs(int u, int p) {
    dp[u][color[u]] = 1;
    for (int v = 0; v < 2; v++) {
        dp[u][v] += dp[p][v ^ color[u]];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d %d %d", &graph[i][0], &graph[i][1], &color[i]);
    }

    // Build the tree using adjacency list representation
    int degree[MAXN] = {0};
    for (int i = 1; i < n; i++) {
        degree[graph[i][0]]++;
        degree[graph[i][1]]++;
    }

    int root = -1;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) {
            root = i;
            break;
        }
    }

    dfs(root, 0);

    long long result = 0;
    for (int i = 1; i < n; i++) {
        result += (long long)dp[graph[i][0]][color[i]] * dp[graph[i][1]][color[i]];
    }

    printf("%lld\n", result / 2);

    return 0;
}