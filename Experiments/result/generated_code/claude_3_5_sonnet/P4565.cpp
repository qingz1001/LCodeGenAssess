#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 366667
#define MAXLOG 19

typedef long long ll;

int n;
int head[MAXN], head2[MAXN], ecnt;
int dep[MAXN], dep2[MAXN], fa[MAXN][MAXLOG], fa2[MAXN][MAXLOG];
ll dis[MAXN], dis2[MAXN];

struct Edge {
    int to, next;
    ll w;
} edge[MAXN * 2], edge2[MAXN * 2];

void add_edge(int u, int v, ll w) {
    edge[ecnt].to = v;
    edge[ecnt].w = w;
    edge[ecnt].next = head[u];
    head[u] = ecnt++;
}

void add_edge2(int u, int v, ll w) {
    edge2[ecnt].to = v;
    edge2[ecnt].w = w;
    edge2[ecnt].next = head2[u];
    head2[u] = ecnt++;
}

void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    for (int i = 1; i < MAXLOG; i++)
        fa[u][i] = fa[fa[u][i-1]][i-1];
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == f) continue;
        dis[v] = dis[u] + edge[i].w;
        dfs(v, u);
    }
}

void dfs2(int u, int f) {
    dep2[u] = dep2[f] + 1;
    fa2[u][0] = f;
    for (int i = 1; i < MAXLOG; i++)
        fa2[u][i] = fa2[fa2[u][i-1]][i-1];
    for (int i = head2[u]; ~i; i = edge2[i].next) {
        int v = edge2[i].to;
        if (v == f) continue;
        dis2[v] = dis2[u] + edge2[i].w;
        dfs2(v, u);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        int t = u; u = v; v = t;
    }
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v) return u;
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int lca2(int u, int v) {
    if (dep2[u] < dep2[v]) {
        int t = u; u = v; v = t;
    }
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (dep2[fa2[u][i]] >= dep2[v])
            u = fa2[u][i];
    if (u == v) return u;
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (fa2[u][i] != fa2[v][i])
            u = fa2[u][i], v = fa2[v][i];
    return fa2[u][0];
}

int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    memset(head2, -1, sizeof(head2));
    
    for (int i = 1; i < n; i++) {
        int x, y;
        ll v;
        scanf("%d%d%lld", &x, &y, &v);
        add_edge(x, y, v);
        add_edge(y, x, v);
    }
    
    ecnt = 0;
    for (int i = 1; i < n; i++) {
        int x, y;
        ll v;
        scanf("%d%d%lld", &x, &y, &v);
        add_edge2(x, y, v);
        add_edge2(y, x, v);
    }
    
    dfs(1, 0);
    dfs2(1, 0);
    
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int l = lca(i, j);
            int l2 = lca2(i, j);
            ll d = dis[i] + dis[j] - dis[l] - dis[l] - dis2[l2] - dis2[l2];
            if (d > ans) ans = d;
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}