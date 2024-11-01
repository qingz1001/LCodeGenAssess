#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 30005
#define MAXLOGN 15

int n, q;
int w[MAXN];
int depth[MAXN];
int fa[MAXN][MAXLOGN];
int max_w[MAXN][MAXLOGN];
int sum_w[MAXN];
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], ecnt;

void add_edge(int u, int v) {
    to[++ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
}

void dfs(int u, int f) {
    depth[u] = depth[f] + 1;
    fa[u][0] = f;
    max_w[u][0] = w[u];
    sum_w[u] = sum_w[f] + w[u];
    
    for (int i = 1; i < MAXLOGN; i++) {
        fa[u][i] = fa[fa[u][i-1]][i-1];
        max_w[u][i] = (w[u] > max_w[fa[u][i-1]][i-1]) ? w[u] : max_w[fa[u][i-1]][i-1];
    }
    
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v != f) dfs(v, u);
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int tmp = u; u = v; v = tmp;
    }
    
    for (int i = MAXLOGN - 1; i >= 0; i--) {
        if (depth[fa[u][i]] >= depth[v]) {
            u = fa[u][i];
        }
    }
    
    if (u == v) return u;
    
    for (int i = MAXLOGN - 1; i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    
    return fa[u][0];
}

int query_max(int u, int v) {
    int l = lca(u, v);
    int res = w[l];
    
    for (int i = MAXLOGN - 1; i >= 0; i--) {
        if (depth[fa[u][i]] >= depth[l]) {
            res = (res > max_w[u][i]) ? res : max_w[u][i];
            u = fa[u][i];
        }
        if (depth[fa[v][i]] >= depth[l]) {
            res = (res > max_w[v][i]) ? res : max_w[v][i];
            v = fa[v][i];
        }
    }
    
    return res;
}

int query_sum(int u, int v) {
    int l = lca(u, v);
    return sum_w[u] + sum_w[v] - 2 * sum_w[l] + w[l];
}

void change(int u, int t) {
    int delta = t - w[u];
    w[u] = t;
    
    for (int i = 0; i < MAXLOGN; i++) {
        max_w[u][i] = (i == 0) ? t : (t > max_w[fa[u][i-1]][i-1]) ? t : max_w[fa[u][i-1]][i-1];
    }
    
    while (u) {
        sum_w[u] += delta;
        u = fa[u][0];
    }
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    
    dfs(1, 0);
    
    scanf("%d", &q);
    
    char op[10];
    int u, v;
    
    while (q--) {
        scanf("%s %d %d", op, &u, &v);
        
        if (strcmp(op, "CHANGE") == 0) {
            change(u, v);
        } else if (strcmp(op, "QMAX") == 0) {
            printf("%d\n", query_max(u, v));
        } else if (strcmp(op, "QSUM") == 0) {
            printf("%d\n", query_sum(u, v));
        }
    }
    
    return 0;
}