#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1001
#define MAX_M 100001

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAX_M], rev_edges[MAX_M];
int head[MAX_N], rev_head[MAX_N], dist[MAX_N], rev_dist[MAX_N];
int n, m, x, edge_cnt, rev_edge_cnt;

void add_edge(Edge *e, int *h, int u, int v, int w, int *cnt) {
    e[*cnt].v = v;
    e[*cnt].w = w;
    e[*cnt].next = h[u];
    h[u] = (*cnt)++;
}

void dijkstra(Edge *e, int *h, int *d, int start) {
    int vis[MAX_N] = {0};
    for (int i = 1; i <= n; i++) d[i] = INT_MAX;
    d[start] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1, min_dist = INT_MAX;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && d[j] < min_dist) {
                u = j;
                min_dist = d[j];
            }
        }
        if (u == -1) break;
        vis[u] = 1;

        for (int j = h[u]; j != -1; j = e[j].next) {
            int v = e[j].v, w = e[j].w;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &x);

    memset(head, -1, sizeof(head));
    memset(rev_head, -1, sizeof(rev_head));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(edges, head, u, v, w, &edge_cnt);
        add_edge(rev_edges, rev_head, v, u, w, &rev_edge_cnt);
    }

    dijkstra(edges, head, dist, x);
    dijkstra(rev_edges, rev_head, rev_dist, x);

    int max_dist = 0;
    for (int i = 1; i <= n; i++) {
        if (i != x) {
            int total_dist = dist[i] + rev_dist[i];
            if (total_dist > max_dist) {
                max_dist = total_dist;
            }
        }
    }

    printf("%d\n", max_dist);

    return 0;
}