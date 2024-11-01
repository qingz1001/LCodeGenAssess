#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define INF 0x3f3f3f3f

int n, m;
int graph[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];

void floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = dist[i][j] < dist[i][k] + dist[k][j] ? dist[i][j] : dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--;
        v--;
        graph[u][v] = w;
        graph[v][u] = w;
        dist[u][v] = w;
        dist[v][u] = w;
    }
    floyd();
    int important_cities = 0;
    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (j != i && k != i && dist[j][k] > dist[j][i] + dist[i][k]) {
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }
        if (flag) {
            printf("%d ", i + 1);
            important_cities++;
        }
    }
    if (!important_cities) {
        printf("No important cities.");
    }
    return 0;
}