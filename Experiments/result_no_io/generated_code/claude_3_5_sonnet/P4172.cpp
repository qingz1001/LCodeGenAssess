#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 1005
#define MAX_M 100005
#define INF 0x3f3f3f3f

typedef struct Edge {
    int to, next, weight;
} Edge;

Edge edges[MAX_M * 2];
int head[MAX_N], dist[MAX_N], cnt;
bool visited[MAX_N];

void init() {
    memset(head, -1, sizeof(head));
    cnt = 0;
}

void add_edge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
}

void dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist));
    memset(visited, false, sizeof(visited));
    dist[start] = 0;

    for (int i = 1; i <= MAX_N; i++) {
        int u = -1, min_dist = INF;
        for (int j = 1; j < MAX_N; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        visited[u] = true;

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
}

int main() {
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);

    init();

    for (int i = 0; i < m; i++) {
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        add_edge(u, v, t);
        add_edge(v, u, t);
    }

    for (int i = 0; i < q; i++) {
        int k, u, v;
        scanf("%d %d %d", &k, &u, &v);

        if (k == 1) {
            dijkstra(u);
            printf("%d\n", dist[v]);
        } else if (k == 2) {
            for (int e = head[u]; e != -1; e = edges[e].next) {
                if (edges[e].to == v) {
                    edges[e].weight = INF;
                    break;
                }
            }
            for (int e = head[v]; e != -1; e = edges[e].next) {
                if (edges[e].to == u) {
                    edges[e].weight = INF;
                    break;
                }
            }
        }
    }

    return 0;
}