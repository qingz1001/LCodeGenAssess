#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 366667
#define MAX_LOG 20

typedef long long ll;

int n;
int head[MAX_N], nxt[MAX_N * 2], to[MAX_N * 2], ecnt;
ll w[MAX_N * 2];

int head2[MAX_N], nxt2[MAX_N * 2], to2[MAX_N * 2], ecnt2;
ll w2[MAX_N * 2];

int dep[MAX_N], fa[MAX_N][MAX_LOG], lg[MAX_N];
ll dis[MAX_N];

int dep2[MAX_N], fa2[MAX_N][MAX_LOG];
ll dis2[MAX_N];

void addEdge(int u, int v, ll wt) {
    to[ecnt] = v; w[ecnt] = wt; nxt[ecnt] = head[u]; head[u] = ecnt++;
    to[ecnt] = u; w[ecnt] = wt; nxt[ecnt] = head[v]; head[v] = ecnt++;
}

void addEdge2(int u, int v, ll wt) {
    to2[ecnt2] = v; w2[ecnt2] = wt; nxt2[ecnt2] = head2[u]; head2[u] = ecnt2++;
    to2[ecnt2] = u; w2[ecnt2] = wt; nxt2[ecnt2] = head2[v]; head2[v] = ecnt2++;
}

void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    for (int i = 1; i < MAX_LOG; i++)
        fa[u][i] = fa[fa[u][i-1]][i-1];
    for (int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if (v == f) continue;
        dis[v] = dis[u] + w[i];
        dfs(v, u);
    }
}

void dfs2(int u, int f) {
    dep2[u] = dep2[f] + 1;
    fa2[u][0] = f;
    for (int i = 1; i < MAX_LOG; i++)
        fa2[u][i] = fa2[fa2[u][i-1]][i-1];
    for (int i = head2[u]; ~i; i = nxt2[i]) {
        int v = to2[i];
        if (v == f) continue;
        dis2[v] = dis2[u] + w2[i];
        dfs2(v, u);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        int tmp = u; u = v; v = tmp;
    }
    for (int i = lg[dep[u]]; i >= 0; i--)
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    if (u == v) return u;
    for (int i = lg[dep[u]]; i >= 0; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int lca2(int u, int v) {
    if (dep2[u] < dep2[v]) {
        int tmp = u; u = v; v = tmp;
    }
    for (int i = lg[dep2[u]]; i >= 0; i--)
        if (dep2[fa2[u][i]] >= dep2[v])
            u = fa2[u][i];
    if (u == v) return u;
    for (int i = lg[dep2[u]]; i >= 0; i--)
        if (fa2[u][i] != fa2[v][i])
            u = fa2[u][i], v = fa2[v][i];
    return fa2[u][0];
}

int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    memset(head2, -1, sizeof(head2));

    for (int i = 1; i < n; i++) {
        int x, y; ll v;
        scanf("%d%d%lld", &x, &y, &v);
        addEdge(x, y, v);
    }

    for (int i = 1; i < n; i++) {
        int x, y; ll v;
        scanf("%d%d%lld", &x, &y, &v);
        addEdge2(x, y, v);
    }

    for (int i = 2; i <= n; i++)
        lg[i] = lg[i/2] + 1;

    dfs(1, 0);
    dfs2(1, 0);

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int l = lca(i, j);
            int l2 = lca2(i, j);
            ll d = dis[i] + dis[j] - dis[l] - dis2[l2];
            if (d > ans) ans = d;
        }
    }

    printf("%lld\n", ans);
    return 0;
}