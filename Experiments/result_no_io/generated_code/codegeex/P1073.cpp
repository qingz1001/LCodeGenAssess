#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXM 500005

int n, m;
int price[MAXN];
int head[MAXN], to[MAXM], next[MAXM], cnt;
int maxf[MAXN], minf[MAXN];
int in[MAXN], out[MAXN];

void add(int x, int y) {
    to[cnt] = y;
    next[cnt] = head[x];
    head[x] = cnt++;
}

void dfs(int u, int fa) {
    maxf[u] = minf[u] = price[u];
    for (int i = head[u]; i != -1; i = next[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        maxf[u] = max(maxf[u], maxf[v]);
        minf[u] = min(minf[u], minf[v]);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y);
        if (z == 2) add(y, x);
    }
    dfs(1, 0);
    printf("%d\n", maxf[n] - minf[n]);
    return 0;
}