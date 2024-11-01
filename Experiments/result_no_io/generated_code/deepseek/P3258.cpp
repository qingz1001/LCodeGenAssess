#include <stdio.h>
#include <stdlib.h>

#define MAXN 300005

typedef struct {
    int to, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], cnt;
int a[MAXN], candy[MAXN], depth[MAXN], parent[MAXN][20];
int n;

void addEdge(int u, int v) {
    edges[cnt].to = v;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u, int p, int d) {
    depth[u] = d;
    parent[u][0] = p;
    for (int i = 1; i < 20; i++) {
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
    }
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    for (int i = 19; i >= 0; i--) {
        if (depth[parent[u][i]] >= depth[v]) {
            u = parent[u][i];
        }
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

void update(int u, int v) {
    candy[u]++;
    candy[v]++;
    int l = lca(u, v);
    candy[l]--;
    if (parent[l][0] != 0) {
        candy[parent[l][0]]--;
    }
}

void dfs2(int u, int p) {
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v != p) {
            dfs2(v, u);
            candy[u] += candy[v];
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    cnt = 0;
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        addEdge(x, y);
        addEdge(y, x);
    }
    dfs(1, 0, 1);
    for (int i = 1; i < n; i++) {
        update(a[i], a[i + 1]);
    }
    dfs2(1, 0);
    for (int i = 2; i <= n; i++) {
        candy[a[i]]--;
    }
    for (int i = 1; i <= n; i++) {
        printf("%d\n", candy[i]);
    }
    return 0;
}