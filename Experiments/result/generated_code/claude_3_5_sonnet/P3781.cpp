#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 25
#define MOD 10007

int n, m, q;
int v[MAXN], fa[MAXN], dep[MAXN], siz[MAXN], son[MAXN], top[MAXN];
int cnt, head[MAXN], to[MAXN << 1], nxt[MAXN << 1];
int dp[MAXN][MAXM], ans[MAXM];

void add_edge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void update(int u) {
    for (int i = 0; i < m; i++) dp[u][i] = 0;
    dp[u][v[u]] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u]) continue;
        update(v);
        for (int j = 0; j < m; j++)
            for (int k = 0; k < m; k++)
                dp[u][j ^ k] = (dp[u][j ^ k] + dp[u][j] * dp[v][k]) % MOD;
    }
    for (int i = 0; i < m; i++) ans[i] = (ans[i] + dp[u][i]) % MOD;
}

void change(int x, int y) {
    v[x] = y;
    while (x) {
        int u = top[x];
        for (int i = 0; i < m; i++) ans[i] = (ans[i] - dp[u][i] + MOD) % MOD;
        update(u);
        x = fa[u];
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    update(1);
    scanf("%d", &q);
    while (q--) {
        char op[10];
        scanf("%s", op);
        if (op[0] == 'C') {
            int x, y;
            scanf("%d%d", &x, &y);
            change(x, y);
        } else {
            int k;
            scanf("%d", &k);
            printf("%d\n", ans[k]);
        }
    }
    return 0;
}