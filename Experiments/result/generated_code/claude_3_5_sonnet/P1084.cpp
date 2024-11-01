#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MAXM 50005
#define INF 0x3f3f3f3f

struct Edge {
    int to, next, w;
} edge[MAXN * 2];

int head[MAXN], tot;
int n, m;
int army[MAXM], dist[MAXN], max_dist[MAXN];
int leaf[MAXN], leaf_cnt;

void add_edge(int u, int v, int w) {
    edge[tot].to = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void dfs1(int u, int fa) {
    int is_leaf = 1;
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        is_leaf = 0;
        dfs1(v, u);
        max_dist[u] = (max_dist[u] > max_dist[v] + edge[i].w) ? max_dist[u] : max_dist[v] + edge[i].w;
    }
    if (is_leaf) leaf[leaf_cnt++] = u;
}

void dfs2(int u, int fa) {
    for (int i = head[u]; ~i; i = edge[i].next) {
        int v = edge[i].to;
        if (v == fa) continue;
        dist[v] = dist[u] + edge[i].w;
        dfs2(v, u);
    }
}

int main() {
    scanf("%d", &n);
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &army[i]);
    }

    dfs1(1, 0);
    dfs2(1, 0);

    int ans = 0;
    for (int i = 0; i < leaf_cnt; i++) {
        int min_dist = INF;
        for (int j = 0; j < m; j++) {
            int d = dist[leaf[i]] - dist[army[j]] + max_dist[army[j]];
            if (d < min_dist) min_dist = d;
        }
        if (min_dist > ans) ans = min_dist;
    }

    printf("%d\n", ans == INF ? -1 : ans);
    return 0;
}