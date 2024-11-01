#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1000005
#define MAXM 1000005

int C, n, m, tot, cnt, len, ans;
int head[MAXN], nxt[MAXN], to[MAXN], fa[MAXN], siz[MAXN], dep[MAXN], son[MAXN], top[MAXN], dfn[MAXN], id[MAXN], rnk[MAXN];
char s[MAXN], t[MAXM];

void add(int u, int v) {
    nxt[++tot] = head[u];
    head[u] = tot;
    to[tot] = v;
}

void dfs1(int x, int f) {
    fa[x] = f;
    siz[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y == f) continue;
        dep[y] = dep[x] + 1;
        dfs1(y, x);
        siz[x] += siz[y];
        if (siz[y] > siz[son[x]]) son[x] = y;
    }
}

void dfs2(int x, int t) {
    top[x] = t;
    dfn[x] = ++cnt;
    id[cnt] = x;
    rnk[x] = len - cnt + 1;
    if (!son[x]) return;
    dfs2(son[x], t);
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y == fa[x] || y == son[x]) continue;
        dfs2(y, y);
    }
}

int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) y = fa[top[y]];
        else x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

int main() {
    scanf("%d", &C);
    while (C--) {
        scanf("%d%d", &n, &m);
        tot = cnt = 0;
        memset(head, 0, sizeof(head));
        memset(fa, 0, sizeof(fa));
        memset(son, 0, sizeof(son));
        memset(siz, 0, sizeof(siz));
        memset(dep, 0, sizeof(dep));
        memset(dfn, 0, sizeof(dfn));
        memset(id, 0, sizeof(id));
        memset(rnk, 0, sizeof(rnk));
        ans = 0;
        scanf("%s", s + 1);
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            add(u, v);
            add(v, u);
        }
        scanf("%s", t + 1);
        len = strlen(t + 1);
        dfs1(1, 0);
        dfs2(1, 1);
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                int x = lca(i, j), l = dep[i] + dep[j] - 2 * dep[x] + 1;
                if (l % len) continue;
                l /= len;
                int k = dfn[i], p = dfn[j], f = 0;
                while (k <= dfn[i] + siz[i] - 1) {
                    if (rnk[id[k]] == 1) f = 1;
                    if (rnk[id[k]] == l) f = 0;
                    if (f) break;
                    k++;
                }
                while (p <= dfn[j] + siz[j] - 1) {
                    if (rnk[id[p]] == 1) f = 1;
                    if (rnk[id[p]] == l) f = 0;
                    if (f) break;
                    p++;
                }
                if (!f) ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}