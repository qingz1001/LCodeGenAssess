#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 200005

typedef struct {
    int u, v, w;
} Edge;

typedef struct {
    int to, next;
} Node;

Node edge[MAXM << 1];
int head[MAXN], tot = 0;
Edge events[MAXM];

void add(int u, int v) {
    edge[++tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot;
}

int n, m;
int fa[MAXN][20], dep[MAXN];
long long maxw[MAXN][20];

void dfs(int u, int f, int w) {
    fa[u][0] = f;
    maxw[u][0] = w;
    dep[u] = dep[f] + 1;
    for (int i = 1; i <= 19; ++i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        maxw[u][i] = max(maxw[u][i - 1], maxw[fa[u][i - 1]][i - 1]);
    }
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == f) continue;
        dfs(v, u, edge[i].w);
    }
}

long long query(int u, int v) {
    if (dep[u] > dep[v]) return query(v, u);
    long long res = -1;
    for (int i = 19; i >= 0; --i) {
        if (dep[fa[v][i]] >= dep[u]) {
            res = max(res, maxw[v][i]);
            v = fa[v][i];
        }
    }
    if (u != v) {
        for (int i = 19; i >= 0; --i) {
            if (fa[u][i] != fa[v][i]) {
                res = max(res, maxw[u][i]);
                res = max(res, maxw[v][i]);
                u = fa[u][i];
                v = fa[v][i];
            }
        }
        res = max(res, maxw[u][0]);
        res = max(res, maxw[v][0]);
    } else {
        res = max(res, maxw[u][0]);
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0, 0);
    for (int i = 1; i <= m; ++i) {
        scanf("%d", &events[i].type);
        if (events[i].type == 0) {
            scanf("%d%d%d", &events[i].u, &events[i].v, &events[i].w);
        }
    }
    for (int i = 1; i <= m; ++i) {
        if (events[i].type == 2) {
            printf("%lld\n", query(events[i].u, events[i].u));
        }
    }
    return 0;
}