#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

struct Edge {
    int to, next, color;
} edge[MAXM];

int head[MAXN], cnt;
int n, ans;
int size[MAXN], f[MAXN], g[MAXN];

void addEdge(int u, int v, int c) {
    edge[++cnt].to = v;
    edge[cnt].color = c;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void dfs1(int u, int fa) {
    size[u] = 1;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (edge[i].color == 0)
            f[u] += f[v] + size[v];
        else
            g[u] += g[v] + size[v];
    }
}

void dfs2(int u, int fa) {
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        int tf = f[1] - f[v] - size[v], tg = g[1] - g[v] - size[v];
        if (edge[i].color == 0) tf += size[1] - size[v];
        else tg += size[1] - size[v];
        if (tf == tg && f[v] == g[v]) ans++;
        dfs2(v, u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        addEdge(u, v, c);
        addEdge(v, u, c);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    printf("%d\n", ans);
    return 0;
}