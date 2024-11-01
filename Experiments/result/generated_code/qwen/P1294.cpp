#include <stdio.h>
#include <stdlib.h>

#define MAXN 21
#define INF 0x3f3f3f3f

int n, m;
int graph[MAXN][MAXN];
int dp[1 << MAXN];

void dfs(int state, int u) {
    if (dp[state] != -1) return;
    dp[state] = 0;
    for (int v = 1; v <= n; v++) {
        if ((state & (1 << v)) && graph[u][v] != INF) {
            dfs(state ^ (1 << v), v);
            dp[state] = dp[state ^ (1 << v)] + graph[u][v];
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INF;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }
    for (int i = 0; i < (1 << n); i++) dp[i] = -1;
    dfs((1 << n) - 1, 1);
    printf("%d\n", dp[(1 << n) - 1]);
    return 0;
}