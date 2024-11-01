#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 2501
#define MAXM 6201

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], dist[MAXN], queue[MAXN];
int n, m, s, t, edge_count = 0;

void add_edge(int u, int v, int w) {
    edges[edge_count].v = v;
    edges[edge_count].w = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void dijkstra(int start) {
    int i, j, u, v, w;
    for (i = 1; i <= n; i++) dist[i] = INT_MAX;
    dist[start] = 0;
    int front = 0, rear = 0;
    queue[rear++] = start;

    while (front != rear) {
        u = queue[front++];
        if (front == MAXN) front = 0;

        for (i = head[u]; i != -1; i = edges[i].next) {
            v = edges[i].v;
            w = edges[i].w;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                queue[rear++] = v;
                if (rear == MAXN) rear = 0;
            }
        }
    }
}

int main() {
    int i, u, v, w;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (i = 1; i <= n; i++) head[i] = -1;

    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dijkstra(s);
    printf("%d\n", dist[t]);

    return 0;
}