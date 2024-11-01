#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAXN 50005
#define MAXM 50005

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
int n, m, S, T;
int dist[MAXN], pre[MAXN];
bool visited[MAXN];

void add_edge(int u, int v, int w) {
    edges[edge_count].v = v;
    edges[edge_count].w = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[start] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, min_dist = INT_MAX;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        visited[u] = true;

        for (int j = head[u]; j != -1; j = edges[j].next) {
            int v = edges[j].v;
            int w = edges[j].w;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pre[v] = u;
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &S, &T);
    for (int i = 1; i <= n; i++) head[i] = -1;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dijkstra(S);
    int dist_ST = dist[T];

    int count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (dist[i] + dist[j] == dist_ST && pre[i] != j && pre[j] != i) {
                count++;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}