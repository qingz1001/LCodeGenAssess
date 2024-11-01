#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXM 300005

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], cnt;
int dfn[MAXN], low[MAXN], fa[MAXN], sdom[MAXN], idom[MAXN], id[MAXN];
int f[MAXN], val[MAXN];
int semi[MAXN], tot;

void add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

int find(int x) {
    if (x == f[x]) return x;
    int tmp = f[x];
    f[x] = find(f[x]);
    if (sdom[val[tmp]] < sdom[val[x]])
        val[x] = val[tmp];
    return f[x];
}

void dfs(int u) {
    dfn[u] = ++tot;
    id[tot] = u;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (!dfn[v]) {
            fa[v] = u;
            dfs(v);
        }
    }
}

void tarjan() {
    for (int i = tot; i >= 2; i--) {
        int x = id[i], p = fa[x];
        sdom[x] = x;
        for (int j = head[x]; j; j = nxt[j]) {
            int y = to[j];
            if (!dfn[y]) continue;
            if (dfn[y] < dfn[x]) {
                if (dfn[y] < sdom[x])
                    sdom[x] = y;
            } else {
                find(y);
                if (dfn[sdom[val[y]]] < dfn[sdom[x]])
                    sdom[x] = sdom[val[y]];
            }
        }
        f[x] = p;
        semi[sdom[x]] = x;
        x = semi[p];
        while (x) {
            find(x);
            if (sdom[val[x]] == sdom[x])
                idom[x] = sdom[x];
            else
                idom[x] = val[x];
            x = semi[p = f[p]];
        }
    }
    for (int i = 2; i <= tot; i++) {
        int x = id[i];
        if (idom[x] != sdom[x])
            idom[x] = idom[idom[x]];
    }
}

int sz[MAXN];

void dfs2(int u) {
    sz[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (idom[v] == u) {
            dfs2(v);
            sz[u] += sz[v];
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
    }
    for (int i = 1; i <= n; i++) {
        f[i] = val[i] = sdom[i] = i;
    }
    dfs(1);
    tarjan();
    dfs2(1);
    for (int i = 1; i <= n; i++) {
        printf("%d ", sz[i]);
    }
    return 0;
}