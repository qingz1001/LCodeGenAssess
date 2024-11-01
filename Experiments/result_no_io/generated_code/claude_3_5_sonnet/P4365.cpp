#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MOD 64123

int n, k, W;
int d[MAXN];
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], cnt;
int size[MAXN], f[MAXN], g[MAXN], sum[MAXN];
long long ans;

void addEdge(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs1(int u, int fa) {
    size[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs1(v, u);
        size[u] += size[v];
    }
}

void dfs2(int u, int fa) {
    f[u] = g[u] = 0;
    sum[u] = d[u];
    int mx1 = 0, mx2 = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs2(v, u);
        if (size[v] > size[mx1]) {
            mx2 = mx1;
            mx1 = v;
        } else if (size[v] > size[mx2]) {
            mx2 = v;
        }
        f[u] += f[v];
        sum[u] += sum[v];
    }
    if (mx1) {
        g[u] = f[mx1] + g[mx1];
        if (mx2) g[u] = (g[u] + f[mx2]) % MOD;
    }
    f[u] = (f[u] + sum[u]) % MOD;
    if (size[u] >= k) ans = (ans + sum[u]) % MOD;
}

int main() {
    scanf("%d%d%d", &n, &k, &W);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        addEdge(x, y);
        addEdge(y, x);
    }
    
    dfs1(1, 0);
    dfs2(1, 0);
    
    printf("%lld\n", ans);
    
    return 0;
}