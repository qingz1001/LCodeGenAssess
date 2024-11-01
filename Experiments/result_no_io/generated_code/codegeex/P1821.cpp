#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1001
#define MAXM 100001

typedef struct {
    int v;
    int w;
} Edge;

Edge graph1[MAXN][MAXN], graph2[MAXN][MAXN];
int dist1[MAXN], dist2[MAXN];
int n, m, x;
int ans = INT_MIN;

void addEdge(Edge graph[MAXN][MAXN], int u, int v, int w) {
    graph[u][v].v = v;
    graph[u][v].w = w;
}

void dijkstra(int graph[MAXN][MAXN], int dist[MAXN], int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    int visited[MAXN] = {0};
    for (int i = 1; i <= n; i++) {
        int minDist = INT_MAX, minNode = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minNode = j;
            }
        }
        if (minNode == -1) break;

        visited[minNode] = 1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && graph[minNode][j].v && dist[minNode] != INT_MAX && dist[minNode] + graph[minNode][j].w < dist[j]) {
                dist[j] = dist[minNode] + graph[minNode][j].w;
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &x);

    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            graph1[i][j].v = 0;
            graph1[i][j].w = 0;
            graph2[i][j].v = 0;
            graph2[i][j].w = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(graph1, u, v, w);
        addEdge(graph2, v, u, w);
    }

    dijkstra(graph1, dist1, x);
    dijkstra(graph2, dist2, x);

    for (int i = 1; i <= n; i++) {
        ans = (dist1[i] + dist2[i] > ans) ? dist1[i] + dist2[i] : ans;
    }

    printf("%d\n", ans);

    return 0;
}