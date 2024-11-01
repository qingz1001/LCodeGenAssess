#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to, next, weight;
} Edge;

int head[MAXN], edge_cnt = 0;
Edge edges[MAXN * 2];

void add_edge(int u, int v, int w) {
    edges[edge_cnt].to = v;
    edges[edge_cnt].next = head[u];
    edges[edge_cnt].weight = w;
    head[u] = edge_cnt++;
}

int n, m;
int army[MAXN];
int visited[MAXN];
int dis[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dis[i] = INF;
    }
    dis[start] = 0;
    for (int i = 1; i <= n - 1; i++) {
        int min_dist = INF, min_index = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dis[j] < min_dist) {
                min_dist = dis[j];
                min_index = j;
            }
        }
        visited[min_index] = 1;
        for (int e = head[min_index]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].weight;
            if (!visited[v] && dis[min_index] + w < dis[v]) {
                dis[v] = dis[min_index] + w;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &army[i]);
    }

    int result = INF;
    for (int i = 0; i < m; i++) {
        dijkstra(army[i]);
        int max_dis = 0;
        for (int j = 1; j <= n; j++) {
            if (dis[j] > max_dis) {
                max_dis = dis[j];
            }
        }
        if (max_dis < result) {
            result = max_dis;
        }
    }

    printf("%d\n", result == INF ? -1 : result);

    return 0;
}