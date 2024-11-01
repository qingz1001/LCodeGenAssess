#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300005
#define MAXM 300005

int n, m;
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], tot;
int w[MAXN], s[MAXM], t[MAXM];
int fa[MAXN], dep[MAXN], siz[MAXN], son[MAXN], top[MAXN];
int dfn[MAXN], rnk[MAXN], cnt;
int tree[MAXN * 4], tag[MAXN * 4];
int ans[MAXN];

void add_edge(int u, int v) {
    to[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
    to[++tot] = u; nxt[tot] = head[v]; head[v] = tot;
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
    top[u] = t; dfn[u] = ++cnt; rnk[cnt] = u;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void pushup(int rt) {
    tree[rt] = tree[rt * 2] + tree[rt * 2 + 1];
}

void pushdown(int rt, int l, int r) {
    if (tag[rt]) {
        int mid = (l + r) / 2;
        tree[rt * 2] += tag[rt] * (mid - l + 1);
        tree[rt * 2 + 1] += tag[rt] * (r - mid);
        tag[rt * 2] += tag[rt];
        tag[rt * 2 + 1] += tag[rt];
        tag[rt] = 0;
    }
}

void update(int rt, int l, int r, int L, int R, int val) {
    if (L <= l && r <= R) {
        tree[rt] += val * (r - l + 1);
        tag[rt] += val;
        return;
    }
    pushdown(rt, l, r);
    int mid = (l + r) / 2;
    if (L <= mid) update(rt * 2, l, mid, L, R, val);
    if (R > mid) update(rt * 2 + 1, mid + 1, r, L, R, val);
    pushup(rt);
}

int query(int rt, int l, int r, int pos) {
    if (l == r) return tree[rt];
    pushdown(rt, l, r);
    int mid = (l + r) / 2;
    if (pos <= mid) return query(rt * 2, l, mid, pos);
    else return query(rt * 2 + 1, mid + 1, r, pos);
}

void update_path(int x, int y, int val) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            int temp = x; x = y; y = temp;
        }
        update(1, 1, n, dfn[top[x]], dfn[x], val);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) {
        int temp = x; x = y; y = temp;
    }
    update(1, 1, n, dfn[x], dfn[y], val);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &s[i], &t[i]);
    }
    
    dfs1(1, 0);
    dfs2(1, 1);
    
    for (int i = 1; i <= m; i++) {
        update_path(s[i], t[i], 1);
        if (dep[s[i]] > dep[t[i]]) {
            int temp = s[i]; s[i] = t[i]; t[i] = temp;
        }
        update(1, 1, n, dfn[t[i]], dfn[t[i]], -1);
    }
    
    for (int i = 1; i <= n; i++) {
        ans[i] = query(1, 1, n, dfn[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        if (w[i] == 0) {
            printf("%d ", ans[i]);
        } else {
            printf("0 ");
        }
    }
    
    return 0;
}