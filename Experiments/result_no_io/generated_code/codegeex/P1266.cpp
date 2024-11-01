#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define N 150
#define M 10000
#define INF LLONG_MAX

typedef struct {
    int to, next, v, l;
} Edge;

Edge edges[M];
int head[N], dist[N][N], path[N][N];
int n, m, d;

void add_edge(int u, int v, int w, int len) {
    static int tot = 0;
    edges[++tot] = (Edge){v, head[u], w, len};
    head[u] = tot;
}

void dijkstra() {
    static long long dist2[N];
    static int vis[N];
    memset(vis, 0, sizeof(vis));
    memset(dist2, 0x3f, sizeof(dist2));
    dist2[0] = 0;
    for (int i = 0; i < n; i++) {
        int u = -1, min = INF;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && dist2[j] < min) {
                u = j;
                min = dist2[j];
            }
        }
        if (u == -1) break;
        vis[u] = 1;
        for (int j = head[u]; j; j = edges[j].next) {
            int v = edges[j].to;
            if (dist2[u] + edges[j].l * 1000 / edges[j].v < dist2[v]) {
                dist2[v] = dist2[u] + edges[j].l * 1000 / edges[j].v;
                path[u][v] = u;
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &d);
    while (m--) {
        int u, v, w, len;
        scanf("%d%d%d%d", &u, &v, &w, &len);
        add_edge(u, v, w, len);
    }
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    dijkstra();
    if (dist2[d] == INF) {
        printf("No solution\n");
        return 0;
    }
    int u = d;
    while (u) {
        for (int i = 0; i < n; i++) {
            if (dist2[u] - edges[head[u]].l * 1000 / edges[head[u]].v == dist2[i]) {
                printf("%d ", i);
                u = i;
                break;
            }
        }
    }
    printf("%d\n", d);
    return 0;
}