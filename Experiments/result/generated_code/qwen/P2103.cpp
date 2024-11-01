#include <stdio.h>
#include <stdlib.h>

#define MAXN 500
#define INF 1e9

int N, M;
int dist[MAXN][MAXN];
int graph[MAXN][MAXN];

void floyd() {
    for (int k = 1; k <= N; ++k) {
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = graph[v][u] = w;
        dist[u][v] = dist[v][u] = w;
    }
    floyd();
    long long result = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (dist[i][j] != INF) {
                result += dist[i][j];
            }
        }
    }
    printf("%lld\n", result);
    return 0;
}