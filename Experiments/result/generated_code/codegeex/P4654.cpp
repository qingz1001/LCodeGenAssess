#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 1000001

int n, t, m;
int fa[MAXN];
int size[MAXN];
int depth[MAXN];
int head[MAXN];
int to[MAXN * 2];
int next[MAXN * 2];
int edge_cnt;

void add_edge(int x, int y) {
    next[++edge_cnt] = head[x];
    head[x] = edge_cnt;
    to[edge_cnt] = y;
}

void dfs(int x, int f) {
    fa[x] = f;
    size[x] = 1;
    for (int i = head[x]; i; i = next[i]) {
        int y = to[i];
        if (y == f) continue;
        depth[y] = depth[x] + 1;
        dfs(y, x);
        size[x] += size[y];
    }
}

int main() {
    scanf("%d %d %d", &n, &t, &m);
    for (int i = 1; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    dfs(t, 0);
    int ans = 0;
    while (m != t) {
        int x = m;
        int y = fa[x];
        int z = fa[y];
        if (depth[x] > depth[y]) {
            x = y;
            y = z;
        }
        ans += depth[x] - depth[y] + 1;
        m = y;
    }
    printf("%d\n", ans);
    return 0;
}