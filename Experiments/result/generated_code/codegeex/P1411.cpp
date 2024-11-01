#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 705
#define MAXM 1505

int n, m, cnt, head[MAXN], f[MAXN], size[MAXN], ans;
struct Edge {
    int to, next;
} edge[MAXM];

void add(int u, int v) {
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}

void dfs(int u, int fa) {
    size[u] = 1;
    f[u] = 1;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        dfs(v, u);
        size[u] += size[v];
        f[u] = f[u] * f[v];
    }
    ans = ans > f[u] ? ans : f[u];
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        f[u] = f[u] / f[v] / size[v] * (size[1] - size[v]);
        ans = ans > f[u] ? ans : f[u];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}