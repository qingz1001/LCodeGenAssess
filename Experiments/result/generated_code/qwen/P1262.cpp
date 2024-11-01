#include <stdio.h>
#include <stdlib.h>

#define MAX_SPIES 3005
#define INF 999999999

typedef struct {
    int value;
    int next;
} Edge;

Edge edges[MAX_SPIES * MAX_SPIES];
int edge_count[MAX_SPIES];
int parent[MAX_SPIES];
int dist[MAX_SPIES];

void add_edge(int u, int v, int w) {
    edges[edge_count[u]].value = w;
    edges[edge_count[u]].next = edge_count[v];
    edge_count[u]++;
}

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_sets(int x, int y) {
    parent[find(x)] = find(y);
}

int bellman_ford(int start, int n) {
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        parent[i] = i;
    }
    dist[start] = 0;

    for (int i = 1; i < n; i++) {
        for (int u = 0; u < n; u++) {
            for (int j = edge_count[u]; j >= 0; j--) {
                int v = edges[j].next;
                int w = edges[j].value;
                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        for (int j = edge_count[u]; j >= 0; j--) {
            int v = edges[j].next;
            int w = edges[j].value;
            if (dist[u] != INF && dist[u] + w < dist[v])
                return -1;
        }
    }

    return dist[n-1];
}

int main() {
    int n, p, r, u, v, w;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        edge_count[i] = -1;

    scanf("%d", &p);
    for (int i = 0; i < p; i++) {
        scanf("%d %d", &u, &w);
        add_edge(u-1, n, w);
    }

    scanf("%d", &r);
    for (int i = 0; i < r; i++) {
        scanf("%d %d", &u, &v);
        add_edge(v-1, u-1, 0);
    }

    int result = bellman_ford(0, n+1);
    if (result == -1) {
        printf("NO\n");
        for (int i = 1; i <= n; i++) {
            if (bellman_ford(i, n+1) == -1) {
                printf("%d\n", i);
                break;
            }
        }
    } else {
        printf("YES\n");
        printf("%d\n", result);
    }

    return 0;
}