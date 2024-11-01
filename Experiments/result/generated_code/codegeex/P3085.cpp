#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

int n, m, u[MAXM], v[MAXM], w[MAXM], head[MAXN], tot, cnt, ans;
int fa[MAXN], dep[MAXN], siz[MAXN], top[MAXN], son[MAXN], id[MAXN], rk[MAXN];
int sum[MAXN][2], num[MAXN][2], num1[MAXN][2], num2[MAXN][2];

struct Edge {
    int to, next, val;
} edge[MAXM];

void add_edge(int from, int to, int val) {
    edge[++tot].to = to;
    edge[tot].val = val;
    edge[tot].next = head[from];
    head[from] = tot;
}

void dfs1(int x, int f) {
    fa[x] = f;
    dep[x] = dep[f] + 1;
    siz[x] = 1;
    for (int i = head[x]; i; i = edge[i].next) {
        int y = edge[i].to;
        if (y == f) continue;
        w[y] = edge[i].val;
        dfs1(y, x);
        siz[x] += siz[y];
        if (siz[y] > siz[son[x]]) son[x] = y;
    }
}

void dfs2(int x, int topf) {
    top[x] = topf;
    id[x] = ++cnt;
    rk[cnt] = x;
    if (!son[x]) return;
    dfs2(son[x], topf);
    for (int i = head[x]; i; i = edge[i].next) {
        int y = edge[i].to;
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

void update(int x, int y, int k) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) y = fa[top[y]];
        else x = fa[top[x]];
        sum[x][k] += w[x] == k ? 1 : -1;
        num[x][k]++;
    }
    if (dep[x] < dep[y]) swap(x, y);
    sum[y][k] += w[y] == k ? 1 : -1;
    num[y][k]++;
}

void dfs(int x) {
    if (son[x]) dfs(son[x]);
    for (int i = head[x]; i; i = edge[i].next) {
        int y = edge[i].to;
        if (y == fa[x] || y == son[x]) continue;
        dfs(y);
        for (int k = 0; k < 2; k++) {
            num1[x][k] += num[y][k];
            num2[x][k] += num[y][k];
            sum[x][k] += sum[y][k];
        }
    }
    for (int i = head[x]; i; i = edge[i].next) {
        int y = edge[i].to;
        if (y == fa[x] || y == son[x]) continue;
        for (int k = 0; k < 2; k++) {
            num2[x][k] -= num[y][k];
            sum[x][k] -= sum[y][k];
        }
        for (int k = 0; k < 2; k++) {
            if (sum[x][k] == 0 && num1[x][k] > 0 && num2[y][k] > 0) ans += num1[x][k] * num2[y][k];
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x, y, z);
        add_edge(y, x, z);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++) {
        update(rk[i], rk[i], w[rk[i]]);
    }
    dfs(1);
    printf("%d\n", ans);
    return 0;
}