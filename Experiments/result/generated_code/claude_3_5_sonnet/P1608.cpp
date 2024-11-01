#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 2000
#define MAX_E 4000000

typedef struct {
    int to, cost;
} Edge;

Edge edges[MAX_E];
int head[MAX_N + 1], nxt[MAX_E], edge_cnt;
int dist[MAX_N + 1], paths[MAX_N + 1];
int N, E;

void add_edge(int from, int to, int cost) {
    edges[edge_cnt].to = to;
    edges[edge_cnt].cost = cost;
    nxt[edge_cnt] = head[from];
    head[from] = edge_cnt++;
}

void dijkstra() {
    int visited[MAX_N + 1] = {0};
    for (int i = 1; i <= N; i++) {
        dist[i] = INT_MAX;
        paths[i] = 0;
    }
    dist[1] = 0;
    paths[1] = 1;

    for (int i = 1; i <= N; i++) {
        int u = -1, min_dist = INT_MAX;
        for (int j = 1; j <= N; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = edges[e].to;
            int cost = edges[e].cost;
            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                paths[v] = paths[u];
            } else if (dist[u] + cost == dist[v]) {
                paths[v] += paths[u];
                if (paths[v] >= (1 << 30)) paths[v] %= (1 << 30);
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &E);
    memset(head, -1, sizeof(head));

    for (int i = 0; i < E; i++) {
        int from, to, cost;
        scanf("%d %d %d", &from, &to, &cost);
        add_edge(from, to, cost);
    }

    dijkstra();

    if (dist[N] == INT_MAX) {
        printf("No answer\n");
    } else {
        printf("%d %d\n", dist[N], paths[N]);
    }

    return 0;
}