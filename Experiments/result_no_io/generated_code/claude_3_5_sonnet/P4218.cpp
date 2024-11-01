#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 50005

typedef long long ll;

int n, m;
char s[MAXN], t[MAXM];
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], ecnt;
int fa[MAXN], dep[MAXN], siz[MAXN], son[MAXN], top[MAXN], dfn[MAXN], rnk[MAXN], dfs_clock;

void add_edge(int u, int v) {
    to[++ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt;
    to[++ecnt] = u; nxt[ecnt] = head[v]; head[v] = ecnt;
}

void dfs1(int u, int f) {
    fa[u] = f; dep[u] = dep[f] + 1; siz[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t; dfn[u] = ++dfs_clock; rnk[dfs_clock] = u;
    if (son[u]) dfs2(son[u], t);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int nxt_pos[MAXM];

void get_next() {
    nxt_pos[0] = nxt_pos[1] = 0;
    for (int i = 1, j = 0; i < m; i++) {
        while (j && t[i] != t[j]) j = nxt_pos[j];
        if (t[i] == t[j]) j++;
        nxt_pos[i + 1] = j;
    }
}

int cnt[MAXN];

void kmp() {
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && s[rnk[i]] != t[j]) j = nxt_pos[j];
        if (s[rnk[i]] == t[j]) j++;
        cnt[i] = j;
        if (j == m) j = nxt_pos[j];
    }
}

ll ans;

void calc(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            int tmp = u; u = v; v = tmp;
        }
        ans += cnt[dfn[u]] - cnt[dfn[top[u]] - 1];
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) {
        int tmp = u; u = v; v = tmp;
    }
    ans += cnt[dfn[v]] - cnt[dfn[u] - 1];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    scanf("%s%s", s + 1, t);
    
    dfs1(1, 0);
    dfs2(1, 1);
    
    get_next();
    kmp();
    
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            calc(i, j);
        }
    }
    
    printf("%lld\n", ans);
    
    return 0;
}