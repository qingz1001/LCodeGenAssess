#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 1005
#define MAX_M 100005
#define INF 0x3f3f3f3f

struct Edge {
    int to, w, next;
} edge[MAX_M];

int head[MAX_N], dist[MAX_N], vis[MAX_N];
int n, m, cnt;

void add_edge(int u, int v, int w) {
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void dijkstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[s] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        vis[u] = 1;

        for (int e = head[u]; e != -1; e = edge[e].next) {
            int v = edge[e].to;
            if (dist[v] > dist[u] + edge[e].w) {
                dist[v] = dist[u] + edge[e].w;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(head, -1, sizeof(head));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    dijkstra(1);

    int total_time = 0;
    for (int i = 2; i <= n; i++) {
        if (dist[i] == INF) {
            printf("-1\n");
            return 0;
        }
        total_time += 2 * dist[i];
    }

    printf("%d\n", total_time);
    return 0;
}