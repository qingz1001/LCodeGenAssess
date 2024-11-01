#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

int n, m, tot, totq;
int fa[MAXN], dep[MAXN], sz[MAXN], son[MAXN], top[MAXN], dfn[MAXN], idx;
char op[MAXN];
int head[MAXN], nxt[MAXM], to[MAXM], qhead[MAXN], qnxt[MAXM], qto[MAXM];

void dfs1(int u) {
    sz[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs1(v);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int tp) {
    top[u] = tp;
    dfn[u] = ++idx;
    if (son[u]) dfs2(son[u], tp);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v != son[u]) dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int get_dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void add_qedge(int u, int v) {
    qto[++totq] = v;
    qnxt[totq] = qhead[u];
    qhead[u] = totq;
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        int x;
        scanf("%d", &x);
        x++;
        add_edge(x, i);
    }
    dep[1] = 1;
    dfs1(1);
    dfs2(1, 1);

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%s", op + 1);
        int x;
        scanf("%d", &x);
        x++;
        if (op[1] == 'i') {
            int cnt = 0;
            for (int j = x; j; j = fa[j]) {
                if (!dep[j]) {
                    cnt++;
                    add_qedge(j, x);
                }
            }
            printf("%d\n", cnt);
            dep[x] = 1;
        } else {
            int cnt = 0;
            for (int j = qhead[x]; j; j = qnxt[j]) {
                int v = qto[j];
                cnt++;
                dep[v] = 0;
            }
            printf("%d\n", cnt);
            for (int j = qhead[x]; j; j = qnxt[j]) {
                int v = qto[j];
                for (int k = v; k; k = fa[k]) {
                    if (!dep[k]) {
                        add_qedge(k, v);
                        dep[k] = 1;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}