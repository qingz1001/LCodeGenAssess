#include <stdio.h>
#include <stdlib.h>

#define MAXN 50010
#define INF 0x3f3f3f3f

typedef struct {
    int to, next, w;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edgeCount;
int dp[MAXN][2];

void addEdge(int from, int to, int w) {
    edges[edgeCount].to = to;
    edges[edgeCount].next = head[from];
    edges[edgeCount].w = w;
    head[from] = edgeCount++;
}

void dfs(int u, int fa) {
    dp[u][0] = INF;
    dp[u][1] = 0;
    for (int i = head[u]; ~i; i = edges[i].next) {
        int v = edges[i].to, w = edges[i].w;
        if (v == fa) continue;
        dfs(v, u);
        dp[u][0] = fmin(dp[u][0], dp[v][0]);
        dp[u][1] = fmin(dp[u][1], dp[v][1]);
    }
    dp[u][0] = fmin(dp[u][0], dp[u][1] + 1);
}

int main() {
    int n, m, u, v, w;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &u);
        dp[u][1] = 0;
    }
    dfs(1, -1);
    int ans = dp[1][0];
    for (int i = 1; i <= n; i++) {
        if (dp[i][1] != 0) {
            ans = -1;
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}