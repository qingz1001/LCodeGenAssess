#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 205
#define MAXM 2005

typedef struct {
    int to, cap, next;
} Edge;

Edge edges[MAXM * 2];
int head[MAXN], edge_count = 0;
int n, m, x;
int dist[MAXN];

void add_edge(int from, int to, int cap) {
    edges[edge_count].to = to;
    edges[edge_count].cap = cap;
    edges[edge_count].next = head[from];
    head[from] = edge_count++;

    edges[edge_count].to = from;
    edges[edge_count].cap = 0;
    edges[edge_count].next = head[to];
    head[to] = edge_count++;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int bfs(int source, int sink) {
    for (int i = 1; i <= n; i++) dist[i] = -1;
    dist[source] = 0;
    int queue[MAXN], front = 0, rear = 0;
    queue[rear++] = source;

    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            if (dist[v] == -1 && edges[i].cap > 0) {
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
            }
        }
    }
    return dist[sink] != -1;
}

int dfs(int u, int sink, int flow) {
    if (u == sink) return flow;
    int actual_flow = 0;
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (dist[v] == dist[u] + 1 && edges[i].cap > 0) {
            int path_flow = dfs(v, sink, min(flow, edges[i].cap));
            if (path_flow > 0) {
                edges[i].cap -= path_flow;
                edges[i ^ 1].cap += path_flow;
                actual_flow += path_flow;
                flow -= path_flow;
                if (flow == 0) break;
            }
        }
    }
    return actual_flow;
}

int dinic(int source, int sink) {
    int max_flow = 0;
    while (bfs(source, sink)) {
        max_flow += dfs(source, sink, INT_MAX);
    }
    return max_flow;
}

int main() {
    scanf("%d %d %d", &n, &m, &x);
    for (int i = 1; i <= n; i++) head[i] = -1;

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        add_edge(a, b, c);
    }

    int max_students_per_batch = dinic(1, n);
    if (max_students_per_batch == 0) {
        printf("Orz Ni Jinan Saint Cow!\n");
    } else {
        int batches = (x + max_students_per_batch - 1) / max_students_per_batch;
        printf("%d %d\n", max_students_per_batch, batches);
    }

    return 0;
}