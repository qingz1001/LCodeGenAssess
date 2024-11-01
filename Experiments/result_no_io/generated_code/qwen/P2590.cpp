#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edgeCount = 0;
int depth[MAXN], parent[MAXN][20], weight[MAXN];

void addEdge(int from, int to) {
    edges[edgeCount].to = to;
    edges[edgeCount].next = head[from];
    head[from] = edgeCount++;
}

void dfs(int node, int prev, int d) {
    depth[node] = d;
    parent[node][0] = prev;
    for (int i = 1; i <= 19; ++i) {
        parent[node][i] = parent[parent[node][i - 1]][i - 1];
    }
    for (int e = head[node]; e != -1; e = edges[e].next) {
        int to = edges[e].to;
        if (to == prev) continue;
        dfs(to, node, d + 1);
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    int diff = depth[v] - depth[u];
    for (int i = 19; i >= 0; --i) {
        if ((diff >> i) & 1) {
            v = parent[v][i];
        }
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

long long querySum(int u, int v) {
    int lcaNode = lca(u, v);
    long long sum = 0;
    while (u != lcaNode) {
        sum += weight[u];
        u = parent[u][0];
    }
    sum += weight[lcaNode];
    while (v != lcaNode) {
        sum += weight[v];
        v = parent[v][0];
    }
    return sum;
}

int queryMax(int u, int v) {
    int lcaNode = lca(u, v);
    int maxVal = -30000;
    while (u != lcaNode) {
        maxVal = (weight[u] > maxVal) ? weight[u] : maxVal;
        u = parent[u][0];
    }
    maxVal = (weight[lcaNode] > maxVal) ? weight[lcaNode] : maxVal;
    while (v != lcaNode) {
        maxVal = (weight[v] > maxVal) ? weight[v] : maxVal;
        v = parent[v][0];
    }
    return maxVal;
}

int main() {
    int n, q;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &weight[i]);
    }
    memset(head, -1, sizeof(head));
    dfs(1, 0, 0);
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        char op[10];
        int u, v;
        scanf("%s", op);
        if (op[0] == 'C') {
            scanf("%d %d", &u, &v);
            weight[u] = v;
        } else if (op[0] == 'Q' && op[1] == 'M') {
            scanf("%d %d", &u, &v);
            printf("%d\n", queryMax(u, v));
        } else if (op[0] == 'Q' && op[1] == 'S') {
            scanf("%d %d", &u, &v);
            printf("%lld\n", querySum(u, v));
        }
    }
    return 0;
}