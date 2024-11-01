#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXM 300005

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], cnt;
int dfn[MAXN], low[MAXN], fa[MAXN], sdom[MAXN], idom[MAXN], id[MAXN];
int f[MAXN], val[MAXN];
int semi[MAXN], dom[MAXN], size[MAXN];
int stack[MAXN], top;
int dfs_clock;

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

int find(int x) {
    if (x == f[x]) return x;
    int root = find(f[x]);
    if (dfn[sdom[val[f[x]]]] < dfn[sdom[val[x]]])
        val[x] = val[f[x]];
    return f[x] = root;
}

void dfs(int u) {
    dfn[u] = ++dfs_clock;
    id[dfs_clock] = u;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            dfs(v);
            fa[v] = u;
        }
    }
}

void tarjan() {
    for (int i = n; i >= 1; i--) {
        int u = id[i];
        for (int j = head[u]; j; j = nxt[j]) {
            int v = to[j];
            if (!dfn[v]) continue;
            find(v);
            if (dfn[sdom[val[v]]] < dfn[sdom[u]])
                sdom[u] = sdom[val[v]];
        }
        if (i != 1) semi[sdom[u]]++;
        f[u] = fa[u];
        for (int j = head[fa[u]]; j; j = nxt[j]) {
            int v = to[j];
            if (dfn[v] > dfn[u]) {
                find(v);
                if (sdom[val[v]] == u) idom[v] = u;
                else idom[v] = val[v];
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        int u = id[i];
        if (idom[u] != sdom[u]) idom[u] = idom[idom[u]];
        dom[idom[u]]++;
    }
}

void dfs2(int u) {
    size[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (idom[v] == u) {
            dfs2(v);
            size[u] += size[v];
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    
    for (int i = 1; i <= n; i++) {
        f[i] = val[i] = sdom[i] = i;
    }
    
    dfs(1);
    tarjan();
    dfs2(1);
    
    for (int i = 1; i <= n; i++) {
        printf("%d ", size[i]);
    }
    
    return 0;
}