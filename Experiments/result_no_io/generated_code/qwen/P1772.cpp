#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f

int n, m, k, e;
int graph[21][21];
int unavailable[21][2];

void floyd() {
    for (int i = 1; i <= m; ++i) {
        graph[i][i] = 0;
    }
    for (int i = 0; i < e; ++i) {
        int u = unavailable[i][0], v = unavailable[i][1];
        for (int j = 1; j <= n; ++j) {
            if (j >= u && j <= v) {
                graph[u][v] = INF;
                graph[v][u] = INF;
            }
        }
    }
    for (int k = 1; k <= m; ++k) {
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (graph[i][k] != INF && graph[k][j] != INF) {
                    graph[i][j] = graph[i][j] > graph[i][k] + graph[k][j] ? graph[i][k] + graph[k][j] : graph[i][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &k, &e);
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j) {
            graph[i][j] = i == j ? 0 : INF;
        }
    }
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        graph[u][v] = graph[v][u] = w;
    }
    floyd();
    int ans = 0, change = 0;
    for (int day = 1; day <= n; ++day) {
        int min_cost = INF, min_node = -1;
        for (int i = 1; i <= m; ++i) {
            if (graph[1][i] != INF && graph[i][m] != INF) {
                if (min_cost > graph[1][i] + graph[i][m]) {
                    min_cost = graph[1][i] + graph[i][m];
                    min_node = i;
                }
            }
        }
        ans += min_cost;
        for (int i = 1; i <= m; ++i) {
            if (graph[1][i] != INF && graph[i][min_node] != INF) {
                graph[1][i] = graph[i][min_node] = INF;
            }
        }
        change++;
    }
    printf("%d\n", ans + k * (change - 1));
    return 0;
}