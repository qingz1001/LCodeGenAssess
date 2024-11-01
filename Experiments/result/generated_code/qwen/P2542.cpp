#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005
#define MAXM 100005

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXM];
int head[MAXN], edgeIndex;
int degree[MAXN];
int parent[MAXN][18];

void addEdge(int u, int v) {
    edges[edgeIndex].to = v;
    edges[edgeIndex].next = head[u];
    head[u] = edgeIndex++;
}

void dfs(int u, int p) {
    parent[u][0] = p;
    for (int i = 1; i <= 17; i++) {
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
    }
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != p) {
            degree[v]++;
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (degree[u] > degree[v]) {
        return lca(v, u);
    }
    for (int i = 17; i >= 0; i--) {
        if ((degree[v] - degree[u]) & (1 << i)) {
            v = parent[v][i];
        }
    }
    if (u == v) return u;
    for (int i = 17; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    edgeIndex = 0;

    dfs(1, -1);

    int q;
    while (scanf("%d", &q) != EOF && q != -1) {
        if (q == 1) {
            int u, v;
            scanf("%d %d", &u, &v);
            int l = lca(u, v);
            int ans = degree[u] + degree[v] - 2 * degree[l];
            printf("%d\n", ans);
        } else if (q == 0) {
            int u, v;
            scanf("%d %d", &u, &v);
            // Remove edge from u to v and v to u
            // Update degrees and parent arrays accordingly
        }
    }

    return 0;
}