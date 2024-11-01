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
    for (int i = 1; i <= n; i++) dist[i] = INT_MAX;
    dist[start] = 0;
    int in_queue[MAXN] = {0};
    int front = 0, rear = 0;
    queue[rear++] = start;
    in_queue[start] = 1;

    while (front != rear) {
        int u = queue[front++];
        if (front == MAXN) front = 0;
        in_queue[u] = 0;

        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v;
            int w = edges[i].w;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!in_queue[v]) {
                    queue[rear++] = v;
                    if (rear == MAXN) rear = 0;
                    in_queue[v] = 1;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &s, &t);
    for (int i = 1; i <= n; i++) head[i] = -1;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dijkstra(s);
    printf("%d\n", dist[t]);

    return 0;
}