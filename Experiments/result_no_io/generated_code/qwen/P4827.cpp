#include <stdio.h>
#include <stdlib.h>

#define MOD 10007

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[100005];
int head[100005], edgeCount;
int degree[100005];
int dp[100005][151];

void addEdge(int from, int to) {
    edges[edgeCount].to = to;
    edges[edgeCount].next = head[from];
    head[from] = edgeCount++;
}

void dfs(int node, int parent, int depth) {
    degree[node] = depth;
    for (int i = head[node]; ~i; i = edges[i].next) {
        int to = edges[i].to;
        if (to == parent) continue;
        dfs(to, node, depth + 1);
        dp[node][1] += dp[to][0];
        dp[node][1] %= MOD;
        dp[node][0] += dp[to][0] * degree[to];
        dp[node][0] %= MOD;
    }
}

void solve(int n, int k) {
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = 1;
    }
    dfs(1, -1, 0);
    for (int i = 2; i <= k; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[j][i] = dp[j][i - 1] * degree[j];
            dp[j][i] %= MOD;
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d\n", (dp[i][k] + dp[i][k - 1]) % MOD);
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    edgeCount = 0;
    for (int i = 1; i <= n; ++i) {
        head[i] = -1;
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    solve(n, k);
    return 0;
}