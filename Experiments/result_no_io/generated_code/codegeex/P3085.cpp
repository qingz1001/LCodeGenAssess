#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100001
#define MAXM 200001

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], cnt;
int col[MAXM];
int f[MAXN][2], g[MAXN][2], ans;

void add(int u, int v, int c) {
    to[++cnt] = v;
    col[cnt] = c;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void dfs(int u, int fa) {
    f[u][0] = f[u][1] = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        f[u][col[i]] += f[v][0] + f[v][1] + 1;
        f[u][col[i]^1] += g[v][0] + g[v][1];
    }
    g[u][0] = f[u][0];
    g[u][1] = f[u][1];
    if (f[u][0] == f[u][1]) ans += 1;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        add(u, v, c);
        add(v, u, c);
    }
    dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}