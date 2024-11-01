#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30005
#define MAXM 100005

int n, m;
int fa[MAXN], size[MAXN], dep[MAXN];
int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], tot;
int dfn[MAXN], low[MAXN], timestamp;
int bridge[MAXM], bridgeCnt;

void addEdge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

int find(int x) {
    return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

void tarjan(int u, int from) {
    dfn[u] = low[u] = ++timestamp;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = low[u] < low[v] ? low[u] : low[v];
            if (low[v] > dfn[u]) {
                bridge[++bridgeCnt] = i;
            }
        } else if (i != (from ^ 1)) {
            low[u] = low[u] < dfn[v] ? low[u] : dfn[v];
        }
    }
}

void dfs(int u, int f) {
    fa[u] = f;
    size[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
        size[u] += size[v];
    }
}

int lca(int u, int v) {
    while (dep[u] > dep[v]) u = fa[u];
    while (dep[v] > dep[u]) v = fa[v];
    while (u != v) {
        u = fa[u];
        v = fa[v];
    }
    return u;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    tarjan(1, 0);

    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 2; i <= tot; i += 2) {
        if (!bridge[i / 2]) {
            int fu = find(to[i]), fv = find(to[i ^ 1]);
            if (fu != fv) fa[fu] = fv;
        }
    }

    memset(head, 0, sizeof(head));
    tot = 1;
    for (int i = 1; i <= bridgeCnt; i++) {
        int e = bridge[i];
        int u = find(to[e ^ 1]), v = find(to[e]);
        addEdge(u, v);
        addEdge(v, u);
    }

    dfs(find(1), 0);

    int op, u, v;
    while (1) {
        scanf("%d", &op);
        if (op == -1) break;
        scanf("%d%d", &u, &v);
        if (op == 1) {
            u = find(u), v = find(v);
            int ancestor = lca(u, v);
            printf("%d\n", dep[u] + dep[v] - 2 * dep[ancestor]);
        } else {
            u = find(u), v = find(v);
            if (dep[u] > dep[v]) {
                int tmp = u;
                u = v;
                v = tmp;
            }
            size[u] -= size[v];
            fa[v] = v;
            dep[v] = 1;
        }
    }

    return 0;
}