#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 200005
#define INF 0x3f3f3f3f

typedef struct {
    int u, v, w;
} Edge;

int n, m, q;
Edge edges[MAXM];
int order[MAXN];
int b[MAXN];
int train_stations[MAXN];
int dist[MAXN];
int parent[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[start] = 0;
    for (int i = 1; i <= n; ++i) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= n; ++j) {
            if (dist[j] < min_dist && !parent[j]) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        parent[u] = 1;
        for (int j = 1; j <= m; ++j) {
            int v = edges[j].v, w = edges[j].w;
            if (u == edges[j].u && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &order[i]);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &b[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    for (int i = 1; i <= q; ++i) {
        scanf("%d", &train_stations[i]);
    }

    for (int i = 1; i <= n; ++i) {
        dijkstra(order[i]);
        if (b[order[i]] > 0) {
            printf("%d\n", b[order[i]]);
        } else {
            printf("0\n");
        }
    }

    return 0;
}