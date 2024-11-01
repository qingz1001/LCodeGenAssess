#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f

typedef struct {
    int to, weight;
} Edge;

int n, m;
int heights[100001];
Edge edges[1000001];

void dijkstra(int start) {
    int dist[100001];
    int visited[100001];
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[start] = 0;
    for (int i = 0; i < n - 1; i++) {
        int u = -1, min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        visited[u] = 1;
        for (int j = 0; j < m; j++) {
            int v = edges[j].to;
            int weight = edges[j].weight;
            if (heights[u] >= heights[v] && !visited[v]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", dist[i]);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &heights[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].weight);
    }
    dijkstra(1);
    return 0;
}