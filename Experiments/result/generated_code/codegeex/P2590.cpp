#include <stdio.h>
#include <string.h>

#define MAXN 30005
#define MAXM 60005

int n, m, cnt;
int head[MAXN], nxt[MAXM], to[MAXM];
int w[MAXN], fa[MAXN], size[MAXN], son[MAXN], top[MAXN], dep[MAXN], id[MAXN], rev[MAXN];

void add(int u, int v) {
    nxt[++cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
}

void dfs1(int u, int f) {
    fa[u] = f;
    size[u] = 1;
    dep[u] = dep[f] + 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    id[u] = ++cnt;
    rev[cnt] = u;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int sum(int x, int y) {
    int ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            x ^= y;
            y ^= x;
            x ^= y;
        }
        ans += w[x] - w[top[x]];
        x = fa[top[x]];
    }
    if (dep[x] < dep[y]) {
        x ^= y;
        y ^= x;
        x ^= y;
    }
    ans += w[x] - w[y];
    return ans;
}

int max(int x, int y) {
    int ans = -30005;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) {
            x ^= y;
            y ^= x;
            x ^= y;
        }
        ans = w[x] > ans ? w[x] : ans;
        x = fa[top[x]];
    }
    if (dep[x] < dep[y]) {
        x ^= y;
        y ^= x;
        x ^= y;
    }
    ans = w[x] > ans ? w[x] : ans;
    ans = w[y] > ans ? w[y] : ans;
    return ans;
}

int main() {
    scanf("%d", &n);
    cnt = 0;
    memset(head, 0, sizeof(head));
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    dfs1(1, 0);
    cnt = 0;
    dfs2(1, 1);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        char op[10];
        int x, y;
        scanf("%s%d%d", op, &x, &y);
        if (op[0] == 'C') {
            w[x] = y;
        } else if (op[1] == 'S') {
            printf("%d\n", sum(x, y));
        } else {
            printf("%d\n", max(x, y));
        }
    }
    return 0;
}