#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[600000];
int head[100005], edgeCount = 0;
int dp[100005][2];
int n, m;

void addEdge(int from, int to) {
    edges[edgeCount].to = to;
    edges[edgeCount].next = head[from];
    head[from] = edgeCount++;
}

int dfs(int u, int parent) {
    dp[u][0] = 0;
    dp[u][1] = dp[u][0] + dp[u][1] + 1;
    for (int e = head[u]; e != -1; e = edges[e].next) {
        int v = edges[e].to;
        if (v == parent) continue;
        int cost = dfs(v, u);
        dp[u][0] += dp[v][0];
        dp[u][1] += dp[v][1];
    }
    return dp[u][0] + dp[u][1];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &dp[i][0]);
        dp[i][1] = 0;
        head[i] = -1;
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        addEdge(x, y);
    }
    long long minCost = 1e18;
    int minWays = 0;
    for (int i = 1; i <= n; ++i) {
        dfs(i, -1);
        if (dp[i][0] < minCost) {
            minCost = dp[i][0];
            minWays = dp[i][1];
        } else if (dp[i][0] == minCost) {
            minWays = (minWays + dp[i][1]) % MOD;
        }
    }
    printf("%lld %d\n", minCost, minWays);
    return 0;
}