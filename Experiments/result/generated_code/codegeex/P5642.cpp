#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 300005
#define MOD 998244353

typedef struct Edge {
    int to;
    int next;
} Edge;

int n, m;
int head[MAXN], edgeCount;
Edge edges[MAXN * 2];
int parent[MAXN], depth[MAXN], size[MAXN], heavy[MAXN], centroid[MAXN];
int dp[MAXN], ans[MAXN][2];

void addEdge(int u, int v) {
    edges[edgeCount].to = v;
    edges[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

void dfs1(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    size[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == p) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[heavy[u]]) heavy[u] = v;
    }
}

void dfs2(int u, int p) {
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == p || v == heavy[u]) continue;
        dfs2(v, u);
        if (dp[v] > dp[heavy[u]]) heavy[u] = v;
    }
    centroid[u] = heavy[u];
}

void decompose(int u, int p) {
    if (centroid[u] != 0) {
        dp[centroid[u]] = dp[u] + 1;
        decompose(centroid[u], u);
    }
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == p || v == centroid[u]) continue;
        decompose(v, u);
    }
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d %d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    decompose(1, 0);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        // TODO: Process each path and update the answer
    }
    printf("%d\n", ans[1][0]);
    return 0;
}