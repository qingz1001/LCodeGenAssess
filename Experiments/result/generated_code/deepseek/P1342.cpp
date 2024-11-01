#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000005
#define MAXM 1000005

typedef struct {
    int to, weight, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
long long dist[MAXN];
int in_queue[MAXN];

void add_edge(int u, int v, int w) {
    edges[edge_count].to = v;
    edges[edge_count].weight = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

void spfa(int start, int n) {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        dist[i] = LLONG_MAX;
        in_queue[i] = 0;
    }
    dist[start] = 0;
    queue[rear++] = start;
    in_queue[start] = 1;

    while (front != rear) {
        int u = queue[front++];
        if (front == MAXN) front = 0;
        in_queue[u] = 0;

        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            int w = edges[i].weight;
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
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) head[i] = -1;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w); // 反向边，用于计算从其他站点回到1号站点的费用
    }

    spfa(1, n);

    long long total_cost = 0;
    for (int i = 1; i <= n; i++) {
        total_cost += dist[i];
    }

    printf("%lld\n", total_cost);
    return 0;
}