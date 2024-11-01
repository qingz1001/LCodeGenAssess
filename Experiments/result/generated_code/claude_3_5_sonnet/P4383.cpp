#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 300005
#define MAX_M 600005

typedef long long ll;

struct Edge {
    int to, next;
    ll w;
} e[MAX_M];

int head[MAX_N], cnt;
int fa[MAX_N], dep[MAX_N], siz[MAX_N], son[MAX_N], top[MAX_N];
ll dis[MAX_N], val[MAX_N];
int n, k;

void add_edge(int u, int v, ll w) {
    e[++cnt] = (struct Edge){v, head[u], w};
    head[u] = cnt;
}

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == f) continue;
        dis[v] = dis[u] + e[i].w;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            int temp = u;
            u = v;
            v = temp;
        }
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

ll get_dis(int u, int v) {
    return dis[u] + dis[v] - 2 * dis[lca(u, v)];
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++) {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
        val[i] = w;
    }

    dfs1(1, 0);
    dfs2(1, 1);

    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ans += val[i] > 0 ? val[i] : 0;
    }

    ll maxdis = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            maxdis = maxdis > get_dis(i, j) ? maxdis : get_dis(i, j);
        }
    }

    printf("%lld\n", ans + maxdis);

    return 0;
}