#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXK 10005

typedef struct {
    int P, C, M;
} Field;

Field fields[MAXN];
int N, K;
int T[MAXK];

typedef struct {
    int to, cap, flow;
} Edge;

typedef struct {
    int v, edge;
} QueueItem;

Edge edges[MAXN * 2];
int edge_count = 0;
int first_edge[MAXN];
int level[MAXN];
int queue[MAXN];

void add_edge(int u, int v, int cap) {
    edges[edge_count] = (Edge){v, cap, 0};
    edges[edge_count + 1] = (Edge){u, 0, 0};
    first_edge[u] = edge_count;
    first_edge[v] = edge_count + 1;
    edge_count += 2;
}

int bfs(int s, int t) {
    int front = 0, rear = 0;
    queue[rear++] = s;
    for (int i = 1; i <= N; i++) level[i] = -1;
    level[s] = 0;
    while (front < rear) {
        int u = queue[front++];
        for (int e = first_edge[u]; e != -1; e = edges[e].to) {
            int v = edges[e].to;
            if (level[v] == -1 && edges[e].flow < edges[e].cap) {
                level[v] = level[u] + 1;
                queue[rear++] = v;
            }
        }
    }
    return level[t] != -1;
}

int dfs(int u, int t, int flow) {
    if (u == t) return flow;
    for (int e = first_edge[u]; e != -1; e = edges[e].to) {
        int v = edges[e].to;
        if (level[v] == level[u] + 1 && edges[e].flow < edges[e].cap) {
            int min_flow = dfs(v, t, flow < edges[e].cap - edges[e].flow ? flow : edges[e].cap - edges[e].flow);
            if (min_flow > 0) {
                edges[e].flow += min_flow;
                edges[e ^ 1].flow -= min_flow;
                return min_flow;
            }
        }
    }
    return 0;
}

int dinic(int s, int t) {
    int total_flow = 0;
    while (bfs(s, t)) {
        int flow;
        while ((flow = dfs(s, t, INT_MAX)) > 0) {
            total_flow += flow;
        }
    }
    return total_flow;
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 1; i <= N; i++) {
        scanf("%d %d %d", &fields[i].P, &fields[i].C, &fields[i].M);
    }
    for (int i = 0; i < K; i++) {
        scanf("%d", &T[i]);
    }

    for (int i = 1; i <= N; i++) {
        add_edge(i, fields[i].P, fields[i].M);
    }

    for (int i = 0; i < K; i++) {
        int max_cows = dinic(1, N);
        printf("%d\n", max_cows);
    }

    return 0;
}