#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 300000
#define MAX_M 300000

int n, m;
int w[MAX_N + 1];
int s[MAX_M], t[MAX_M];
int head[MAX_N + 1], to[MAX_N * 2], next[MAX_N * 2], edge_cnt;
int depth[MAX_N + 1], fa[MAX_N + 1], size[MAX_N + 1];
int in[MAX_N + 1], out[MAX_N + 1];
long long ans[MAX_N + 1];

void add_edge(int u, int v) {
    to[++edge_cnt] = v;
    next[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void dfs1(int u, int f) {
    depth[u] = depth[f] + 1;
    fa[u] = f;
    size[u] = 1;
    for (int i = head[u]; i; i = next[i]) {
        int v = to[i];
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
    }
}

void dfs2(int u, int f) {
    in[u] = ++edge_cnt;
    for (int i = head[u]; i; i = next[i]) {
        int v = to[i];
        if (v == f) continue;
        dfs2(v, u);
    }
    out[u] = edge_cnt;
}

void update(int x, long long val) {
    for (; x <= n; x += x & -x)
        ans[x] += val;
}

long long query(int x) {
    long long res = 0;
    for (; x; x -= x & -x)
        res += ans[x];
    return res;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }

    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i]);

    for (int i = 1; i <= m; i++)
        scanf("%d %d", &s[i], &t[i]);

    dfs1(1, 0);
    edge_cnt = 0;
    dfs2(1, 0);

    for (int i = 1; i <= m; i++) {
        int u = s[i], v = t[i];
        if (depth[u] > depth[v]) {
            int temp = u;
            u = v;
            v = temp;
        }
        int lca = u;
        while (depth[u] != depth[v]) {
            update(in[v], 1);
            update(in[fa[v]], -1);
            v = fa[v];
        }
        while (u != v) {
            update(in[u], 1);
            update(in[fa[u]], -1);
            update(in[v], 1);
            update(in[fa[v]], -1);
            u = fa[u];
            v = fa[v];
        }
        update(in[lca], 1);
        update(in[fa[lca]], -1);
    }

    for (int i = 1; i <= n; i++) {
        long long res = query(out[i]) - query(in[i] - 1);
        if (w[i] >= depth[i] - 1)
            res += query(in[i]);
        printf("%lld ", res);
    }

    return 0;
}