#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 1001

int n, m;
int dist[MAXN];

struct Edge {
    int to, weight;
};

struct Edge graph[MAXN][MAXN];

void addEdge(int u, int v, int w) {
    graph[u][v].to = v;
    graph[u][v].weight = w;
    graph[v][u].to = u;
    graph[v][u].weight = w;
}

void dijkstra(int start) {
    memset(dist, 0x3f, sizeof(dist)); // Initialize distances to infinity
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (dist[j] < INT_MAX && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        for (int v = 1; v <= n; v++) {
            if (graph[u][v].weight != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v].weight < dist[v]) {
                dist[v] = dist[u] + graph[u][v].weight;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    dijkstra(1); // Run Dijkstra's algorithm from city 1
    int maxTime = dist[n]; // The shortest path from city 1 to city N

    dijkstra(n); // Run Dijkstra's algorithm from city N
    int secondMaxTime = dist[1]; // The shortest path from city N to city 1

    printf("%d\n", (maxTime > secondMaxTime) ? maxTime : secondMaxTime);

    return 0;
}