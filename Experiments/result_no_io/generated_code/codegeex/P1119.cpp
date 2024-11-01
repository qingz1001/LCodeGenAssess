#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200
#define MAXM (MAXN * (MAXN - 1) / 2)
#define MAXQ 50000

int N, M, Q;
int rebuild_time[MAXN];
int graph[MAXN][MAXN];
int dist[MAXN];

void floyd_warshall() {
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (graph[i][k] != INT_MAX && graph[k][j] != INT_MAX) {
                    graph[i][j] = (graph[i][j] != INT_MAX && graph[i][j] < graph[i][k] + graph[k][j]) ? graph[i][j] : graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &rebuild_time[i]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            graph[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    floyd_warshall();

    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);
        if (rebuild_time[x] > t || rebuild_time[y] > t) {
            printf("-1\n");
        } else {
            if (graph[x][y] == INT_MAX) {
                printf("-1\n");
            } else {
                printf("%d\n", graph[x][y]);
            }
        }
    }

    return 0;
}