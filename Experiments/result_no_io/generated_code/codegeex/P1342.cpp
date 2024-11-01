#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000001

int n, m;
int dist[MAXN];
int visited[MAXN];

typedef struct {
    int v;
    int w;
} Edge;

Edge graph[MAXN * 2];

void addEdge(int u, int v, int w) {
    static int cnt = 0;
    graph[cnt].v = v;
    graph[cnt].w = w;
    cnt++;
}

void bellmanFord(int start) {
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < 2 * m; j++) {
            if (dist[graph[j].v] > dist[graph[j].v] + graph[j].w) {
                dist[graph[j].v] = dist[graph[j].v] + graph[j].w;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u - 1, v - 1, w);
        addEdge(v - 1, u - 1, w);
    }

    bellmanFord(0);

    int totalCost = 0;
    for (int i = 0; i < n; i++) {
        totalCost += dist[i];
    }

    printf("%d\n", totalCost);

    return 0;
}