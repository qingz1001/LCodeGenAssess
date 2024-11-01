#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define MAXP 10001

typedef struct {
    int u, v, w;
} Edge;

int n, p, k;
Edge edges[MAXP];
int dist[MAXN];
int visited[MAXN];

int compare(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->w - edgeB->w;
}

int bellmanFord(int src, int dest) {
    for (int i = 0; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int j = 0; j < p; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            return -1;
        }
    }

    return dist[dest];
}

int main() {
    scanf("%d%d%d", &n, &p, &k);
    for (int i = 0; i < p; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, p, sizeof(Edge), compare);

    int minCost = bellmanFord(1, n);
    if (minCost == -1) {
        printf("-1\n");
    } else {
        int totalCost = 0;
        int usedFreeCables = 0;
        for (int i = 0; i < p; i++) {
            if (usedFreeCables < k) {
                usedFreeCables++;
            } else {
                totalCost += edges[i].w;
            }
        }
        printf("%d\n", totalCost);
    }

    return 0;
}