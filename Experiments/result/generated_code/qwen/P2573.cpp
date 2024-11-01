#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define INF 1e9

typedef struct Edge {
    int to, weight;
    struct Edge *next;
} Edge;

Edge *adj[MAXN];
int height[MAXN];
int visited[MAXN];
int dp[MAXN][2];

void add_edge(int u, int v, int w) {
    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    new_edge->to = v;
    new_edge->weight = w;
    new_edge->next = adj[u];
    adj[u] = new_edge;
}

void dfs(int u, int parent) {
    visited[u] = 1;
    dp[u][0] = 0;
    dp[u][1] = height[u];

    for (Edge *e = adj[u]; e != NULL; e = e->next) {
        if (e->to == parent || height[e->to] >= height[u]) continue;
        dfs(e->to, u);
        dp[u][0] += dp[e->to][0];
        dp[u][1] += dp[e->to][1];
        if (dp[e->to][0] + e->weight < dp[u][0]) {
            dp[u][0] = dp[e->to][0] + e->weight;
            dp[u][1] = dp[e->to][1];
        } else if (dp[e->to][0] + e->weight == dp[u][0]) {
            dp[u][1] = dp[e->to][1] > dp[u][1] ? dp[e->to][1] : dp[u][1];
        }
    }

    dp[u][0] -= dp[u][1];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &height[i]);
        adj[i] = NULL;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dfs(1, -1);

    printf("%d %d\n", dp[1][0], dp[1][1]);

    return 0;
}