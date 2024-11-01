#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MAXM 50005
#define INF 0x3f3f3f3f

struct Edge {
    int to, next, w;
} edge[MAXN * 2];

int head[MAXN], cnt;
int n, m;
int army[MAXM], f[MAXN], g[MAXN], size[MAXN];
int ans = INF;

void addEdge(int u, int v, int w) {
    edge[++cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void dfs1(int u, int fa) {
    size[u] = army[u];
    f[u] = 0;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs1(v, u);
        size[u] += size[v];
        f[u] = f[u] > f[v] + edge[i].w ? f[u] : f[v] + edge[i].w;
    }
    if (size[u] == 0 && u != 1) f[u] = INF;
}

void dfs2(int u, int fa) {
    int max1 = 0, max2 = 0;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        if (f[v] + edge[i].w >= max1) {
            max2 = max1;
            max1 = f[v] + edge[i].w;
        } else if (f[v] + edge[i].w > max2) {
            max2 = f[v] + edge[i].w;
        }
    }
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        g[v] = g[u] > max1 ? g[u] : max1;
        if (f[v] + edge[i].w == max1) g[v] = g[v] > max2 ? g[v] : max2;
        g[v] = g[v] > edge[i].w ? g[v] : edge[i].w;
        dfs2(v, u);
    }
    int temp = f[u] > g[u] ? f[u] : g[u];
    if (u != 1 && temp < ans) ans = temp;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int x;
        scanf("%d", &x);
        army[x] = 1;
    }
    dfs1(1, 0);
    dfs2(1, 0);
    if (ans == INF) printf("-1\n");
    else printf("%d\n", ans);
    return 0;
}