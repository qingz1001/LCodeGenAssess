#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30005
#define MAXM 60005

int n, q;
int w[MAXN];
int head[MAXN], to[MAXM], nxt[MAXM], tot;
int dep[MAXN], fa[MAXN][16], dis[MAXN];
int mx[MAXN][16], sum[MAXN];

void add_edge(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    for (int i = 1; i < 16; i++) {
        fa[u][i] = fa[fa[u][i-1]][i-1];
        mx[u][i] = (w[u] > mx[fa[u][i-1]][i-1]) ? w[u] : mx[fa[u][i-1]][i-1];
    }
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f) continue;
        dfs(v, u);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        int t = u; u = v; v = t;
    }
    for (int i = 15; i >= 0; i--) {
        if (dep[fa[u][i]] >= dep[v]) {
            u = fa[u][i];
        }
    }
    if (u == v) return u;
    for (int i = 15; i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int query_max(int u, int v) {
    int ans = -1e9;
    int l = lca(u, v);
    for (int i = 15; i >= 0; i--) {
        if (dep[fa[u][i]] >= dep[l]) {
            ans = (ans > mx[u][i]) ? ans : mx[u][i];
            u = fa[u][i];
        }
    }
    for (int i = 15; i >= 0; i--) {
        if (dep[fa[v][i]] >= dep[l]) {
            ans = (ans > mx[v][i]) ? ans : mx[v][i];
            v = fa[v][i];
        }
    }
    ans = (ans > w[l]) ? ans : w[l];
    return ans;
}

int query_sum(int u, int v) {
    int l = lca(u, v);
    return sum[u] + sum[v] - 2 * sum[l] + w[l];
}

void update(int u, int val) {
    int diff = val - w[u];
    w[u] = val;
    for (int i = u; i; i = fa[i][0]) {
        sum[i] += diff;
    }
    for (int i = 0; i < 16; i++) {
        mx[u][i] = val;
        u = fa[u][i];
        if (!u) break;
        if (mx[u][i] > val) break;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[fa[i][0]] + w[i];
    }
    scanf("%d", &q);
    char op[10];
    int u, v;
    while (q--) {
        scanf("%s%d%d", op, &u, &v);
        if (op[0] == 'C') {
            update(u, v);
        } else if (op[1] == 'M') {
            printf("%d\n", query_max(u, v));
        } else {
            printf("%d\n", query_sum(u, v));
        }
    }
    return 0;
}