#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 205
#define INF 0x3f3f3f3f

int n, m;
int graph[MAXN][MAXN];
int dist[MAXN][MAXN];
int importantCities[MAXN];

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j && i != k && j != k) {
                    dist[i][j] = dist[i][j] < dist[i][k] + dist[k][j] ? dist[i][j] : dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

void findImportantCities() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                int originalDist = dist[i][j];
                graph[i][j] = INF;
                floyd();
                if (dist[i][j] > originalDist) {
                    importantCities[i] = 1;
                    break;
                }
                graph[i][j] = originalDist;
                floyd();
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(graph, INF, sizeof(graph));
    memset(dist, INF, sizeof(dist));
    memset(importantCities, 0, sizeof(importantCities));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
        dist[u][v] = w;
        dist[v][u] = w;
    }

    floyd();

    findImportantCities();

    int foundImportantCity = 0;
    for (int i = 1; i <= n; i++) {
        if (importantCities[i]) {
            printf("%d ", i);
            foundImportantCity = 1;
        }
    }

    if (!foundImportantCity) {
        printf("No important cities.");
    }

    return 0;
}