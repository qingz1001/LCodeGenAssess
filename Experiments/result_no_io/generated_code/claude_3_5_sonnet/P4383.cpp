#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300005
#define MAXM 600005

typedef long long ll;

struct Edge {
    int to, next;
    ll w;
} e[MAXM];

int head[MAXN], cnt;
int fa[MAXN], dep[MAXN], siz[MAXN], son[MAXN], top[MAXN];
ll dis[MAXN];
int n, k;

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
}

void addEdge(int u, int v, ll w) {
    e[cnt] = (struct Edge){v, head[u], w};
    head[u] = cnt++;
    e[cnt] = (struct Edge){u, head[v], w};
    head[v] = cnt++;
}

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    for (int i = head[u]; ~i; i = e[i].next) {
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
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            int temp = u; u = v; v = temp;
        }
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

ll dist(int u, int v) {
    return dis[u] + dis[v] - 2 * dis[lca(u, v)];
}

ll edges[MAXN];
int m;

int cmp(const void *a, const void *b) {
    return *(ll*)b - *(ll*)a;
}

int main() {
    scanf("%d%d", &n, &k);
    init();
    for (int i = 1; i < n; i++) {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        addEdge(u, v, w);
        edges[i-1] = w;
    }
    
    dfs1(1, 0);
    dfs2(1, 1);
    
    qsort(edges, n-1, sizeof(ll), cmp);
    
    ll ans = 0;
    for (int i = 0; i < k; i++) {
        if (edges[i] < 0) ans -= edges[i];
    }
    
    ll max_dist = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            ll d = dist(i, j);
            if (d > max_dist) max_dist = d;
        }
    }
    
    ans += max_dist;
    
    printf("%lld\n", ans);
    
    return 0;
}