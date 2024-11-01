#include <stdio.h>
#include <stdlib.h>

#define MOD 786433
#define MAXN 200005

typedef long long ll;

int n;
int a[MAXN];
int head[MAXN], to[MAXN * 2], next[MAXN * 2], idx;
int depth[MAXN], parent[MAXN][20], bitwise_and[MAXN][20];

void add_edge(int u, int v) {
    to[idx] = v;
    next[idx] = head[u];
    head[u] = idx++;
}

void dfs(int u, int p) {
    depth[u] = depth[p] + 1;
    parent[u][0] = p;
    bitwise_and[u][0] = a[u];
    for (int i = 1; i < 20; i++) {
        parent[u][i] = parent[parent[u][i - 1]][i - 1];
        bitwise_and[u][i] = bitwise_and[u][i - 1] & bitwise_and[parent[u][i - 1]][i - 1];
    }
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = to[i];
        if (v != p) {
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }
    int diff = depth[u] - depth[v];
    int result = a[u] & a[v];
    for (int i = 0; i < 20; i++) {
        if ((diff >> i) & 1) {
            result &= bitwise_and[u][i];
            u = parent[u][i];
        }
    }
    if (u == v) return result;
    for (int i = 19; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            result &= bitwise_and[u][i];
            result &= bitwise_and[v][i];
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    result &= a[u];
    result &= a[v];
    return result;
}

ll power_mod(ll base, ll exp, ll mod) {
    ll result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        head[i] = -1;
    }
    idx = 0;
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, 0);
    ll result = 0;
    for (int u = 1; u <= n; u++) {
        for (int v = u; v <= n; v++) {
            int f_uv = lca(u, v);
            if (f_uv == 0) continue;
            result = (result + power_mod(f_uv, f_uv, MOD)) % MOD;
        }
    }
    printf("%lld\n", result);
    return 0;
}