#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define MOD 786433

typedef long long ll;

int n, a[MAX_N];
int head[MAX_N], to[MAX_N * 2], nxt[MAX_N * 2], tot;
int dep[MAX_N], fa[MAX_N][20], val[MAX_N][20];

void add_edge(int u, int v) {
    to[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
    to[++tot] = u; nxt[tot] = head[v]; head[v] = tot;
}

void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    fa[u][0] = f;
    val[u][0] = a[u] & a[f];
    for (int i = 1; i < 20; i++) {
        fa[u][i] = fa[fa[u][i-1]][i-1];
        val[u][i] = val[u][i-1] & val[fa[u][i-1]][i-1];
    }
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v != f) dfs(v, u);
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        int tmp = u; u = v; v = tmp;
    }
    int diff = dep[u] - dep[v];
    for (int i = 19; i >= 0; i--) {
        if (diff & (1 << i)) u = fa[u][i];
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int get_and(int u, int v) {
    int lca_node = lca(u, v);
    int res = a[lca_node];
    while (u != lca_node) {
        res &= a[u];
        u = fa[u][0];
    }
    while (v != lca_node) {
        res &= a[v];
        v = fa[v][0];
    }
    return res;
}

ll quick_pow(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    
    dfs(1, 0);
    
    ll ans = 0;
    for (int u = 1; u <= n; u++) {
        for (int v = u; v <= n; v++) {
            int f = get_and(u, v);
            if (f == 0) continue;
            ans = (ans + quick_pow(f, f)) % MOD;
        }
    }
    
    printf("%lld\n", ans);
    
    return 0;
}