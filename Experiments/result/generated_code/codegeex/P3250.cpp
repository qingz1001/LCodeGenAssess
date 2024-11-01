#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

struct Edge {
    int to, next;
} edge[MAXN * 2];

int head[MAXN], edgeCount;

void addEdge(int u, int v) {
    edge[edgeCount].to = v;
    edge[edgeCount].next = head[u];
    head[u] = edgeCount++;
}

int parent[MAXN], depth[MAXN], size[MAXN], heavy[MAXN], chainHead[MAXN], chainCount;

void dfs1(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    size[u] = 1;
    int maxSubtreeSize = 0;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (v == p) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > maxSubtreeSize) {
            maxSubtreeSize = size[v];
            heavy[u] = v;
        }
    }
}

void dfs2(int u, int chain) {
    chainHead[u] = chain;
    if (heavy[u] != -1) dfs2(heavy[u], chain);
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (v == parent[u] || v == heavy[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (chainHead[u] != chainHead[v]) {
        if (depth[chainHead[u]] > depth[chainHead[v]]) u = parent[chainHead[u]];
        else v = parent[chainHead[v]];
    }
    return depth[u] < depth[v] ? u : v;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(1, -1);
    dfs2(1, 1);
    int activeRequests[MAXN];
    memset(activeRequests, 0, sizeof(activeRequests));
    for (int i = 1; i <= m; i++) {
        int type;
        scanf("%d", &type);
        if (type == 0) {
            int a, b, v;
            scanf("%d %d %d", &a, &b, &v);
            int u = lca(a, b);
            activeRequests[a] = i;
            activeRequests[b] = i;
            activeRequests[u] = i;
        } else if (type == 1) {
            int t;
            scanf("%d", &t);
            activeRequests[t] = 0;
        } else if (type == 2) {
            int x;
            scanf("%d", &x);
            int maxImportance = -1;
            for (int j = head[x]; j != -1; j = edge[j].next) {
                int v = edge[j].to;
                if (activeRequests[v] > i) {
                    maxImportance = i;
                    break;
                }
            }
            printf("%d\n", maxImportance);
        }
    }
    return 0;
}