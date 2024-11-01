#include <stdio.h>
#include <stdlib.h>

#define MAXN 305
#define INF 0x3f3f3f3f

int n, s;
int graph[MAXN][MAXN];
int dist[MAXN];

void dijkstra(int start) {
    for (int i = 1; i <= n; i++) dist[i] = INF;
    dist[start] = 0;
    int visited[MAXN] = {0};
    for (int i = 1; i <= n; i++) {
        int minDist = INF, minIdx = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIdx = j;
            }
        }
        visited[minIdx] = 1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && graph[minIdx][j] != INF) {
                dist[j] = fmin(dist[j], dist[minIdx] + graph[minIdx][j]);
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INF;
        }
    }
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    int center = 1;
    for (int i = 2; i <= n; i++) {
        dijkstra(i);
        int maxDist = 0;
        for (int j = 1; j <= n; j++) {
            maxDist = fmax(maxDist, dist[j]);
        }
        if (maxDist < dist[center]) center = i;
    }

    dijkstra(center);
    int eccentricity = 0;
    for (int i = 1; i <= n; i++) {
        eccentricity = fmax(eccentricity, dist[i]);
    }

    printf("%d\n", eccentricity);

    return 0;
}