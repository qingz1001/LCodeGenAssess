#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 300005
#define MAXM 300005
#define INF LLONG_MAX

typedef long long ll;

struct Edge {
    int to, next;
    ll weight;
} edges[MAXM];

int head[MAXN], edgeCount;
ll dp[MAXN][3];
ll edgeValues[MAXM];

void addEdge(int u, int v, ll w) {
    edges[edgeCount].to = v;
    edges[edgeCount].weight = w;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void dfs(int u, int parent) {
    dp[u][0] = dp[u][1] = dp[u][2] = -INF;
    dp[u][0] = 0;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        ll w = edges[i].weight;
        if (v == parent) continue;
        dfs(v, u);
        dp[u][0] = dp[u][0] + max({dp[v][0], dp[v][1], dp[v][2]});
        dp[u][1] = dp[u][1] + dp[v][0];
        dp[u][2] = dp[u][2] + dp[v][1];
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
        edgeValues[i] = w;
    }

    dfs(1, -1);

    ll ans = -INF;
    for (int i = 0; i < n - 1; i++) {
        int u = edges[i * 2].to;
        int v = edges[i * 2].to;
        ll w = edges[i * 2].weight;
        ans = max(ans, dp[u][0] + dp[v][0] - w);
    }

    ans = max(ans, dp[1][0]);
    printf("%lld\n", ans);
    return 0;
}