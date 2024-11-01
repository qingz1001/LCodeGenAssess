#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 20005
#define MAXK 500005

int n, k;
int fa[MAXN], a[MAXN], v[MAXN];
int son[MAXN], nxt[MAXN], head[MAXN], cnt;
long long f[MAXN][MAXK], g[MAXN][MAXK];

void add(int u, int v) {
    son[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs(int u) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = son[i];
        dfs(v);
        for (int j = k; j >= 0; j--) {
            for (int l = 0; l <= j; l++) {
                f[u][j] = (f[u][j] > f[u][j-l] + f[v][l]) ? f[u][j] : f[u][j-l] + f[v][l];
                g[u][j] = (g[u][j] > g[u][j-l] + g[v][l]) ? g[u][j] : g[u][j-l] + g[v][l];
            }
        }
    }
    for (int i = k; i >= 0; i--) {
        int t = (a[u] < i) ? a[u] : i;
        f[u][i] = g[u][i] + (long long)t * v[u];
        g[u][i] = g[u][i] + (long long)t * v[u];
    }
}

int main() {
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        scanf("%d%d", &n, &k);
        memset(head, 0, sizeof(head));
        cnt = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", &fa[i], &a[i], &v[i]);
            if (i > 1) add(fa[i], i);
        }
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        dfs(1);
        printf("%lld\n", f[1][k]);
    }
    return 0;
}