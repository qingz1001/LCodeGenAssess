#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MAX_M 100001
#define INF 0x3f3f3f3f

struct Edge {
    int v, w, next;
} edges[MAX_M];

int head[MAX_N], dist[MAX_N], vis[MAX_N];
int n, m, cnt;

void addEdge(int u, int v, int w) {
    edges[++cnt].v = v;
    edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt;
}

void dijkstra(int s) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    dist[s] = 0;

    for (int i = 1; i <= n; i++) {
        int u = 0, min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == 0) break;
        vis[u] = 1;

        for (int e = head[u]; e; e = edges[e].next) {
            int v = edges[e].v, w = edges[e].w;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    dijkstra(1);
    
    int total_time = 0;
    for (int i = 2; i <= n; i++) {
        total_time += dist[i];
    }

    dijkstra(1);
    
    for (int i = 2; i <= n; i++) {
        total_time += dist[i];
    }

    printf("%d\n", total_time);
    return 0;
}