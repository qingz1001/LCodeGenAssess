#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1500
#define MAXM 50000

typedef struct {
    int v, w, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], indegree[MAXN], dist[MAXN], queue[MAXN];
int n, m, edge_count = 0;

void add_edge(int u, int v, int w) {
    edges[edge_count].v = v;
    edges[edge_count].w = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
    indegree[v]++;
}

int longest_path() {
    int front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MIN;
    }
    dist[1] = 0;

    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v;
            int w = edges[i].w;
            if (dist[u] != INT_MIN && dist[u] + w > dist[v]) {
                dist[v] = dist[u] + w;
            }
            if (--indegree[v] == 0) {
                queue[rear++] = v;
            }
        }
    }

    return dist[n] == INT_MIN ? -1 : dist[n];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        indegree[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }

    printf("%d\n", longest_path());
    return 0;
}