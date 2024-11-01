#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAXN 100001
#define MAXM 500001

int n, m;
int price[MAXN];
int head[MAXN], next[MAXM], to[MAXM], edge[MAXM];
int maxf[MAXN], minf[MAXN];
bool vis[MAXN];

void addEdge(int x, int y, int z) {
    static int tot = 0;
    next[++tot] = head[x];
    head[x] = tot;
    to[tot] = y;
    edge[tot] = z;
}

void dfs(int u, int fa) {
    maxf[u] = price[u];
    minf[u] = price[u];
    for (int i = head[u]; i; i = next[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        maxf[u] = (maxf[u] > maxf[v] ? maxf[u] : maxf[v]);
        minf[u] = (minf[u] < minf[v] ? minf[u] : minf[v]);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &price[i]);
    }
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addEdge(x, y, z);
        if (z == 2) {
            addEdge(y, x, z);
        }
    }
    dfs(1, 0);
    int maxProfit = 0;
    for (int i = 1; i <= n; i++) {
        maxProfit = (maxProfit > (maxf[i] - minf[i]) ? maxProfit : (maxf[i] - minf[i]));
    }
    printf("%d\n", maxProfit);
    return 0;
}