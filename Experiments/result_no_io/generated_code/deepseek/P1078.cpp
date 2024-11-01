#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 101
#define MAXK 101

int N, K, M, S, T;
int culture[MAXN];
int排斥[MAXK][MAXK];
int dist[MAXN][MAXN];
int visited[MAXN];
int minDist[MAXN];

void dijkstra() {
    for (int i = 1; i <= N; i++) {
        minDist[i] = INT_MAX;
        visited[i] = 0;
    }
    minDist[S] = 0;

    for (int count = 0; count < N - 1; count++) {
        int min = INT_MAX, min_index;

        for (int v = 1; v <= N; v++)
            if (!visited[v] && minDist[v] <= min)
                min = minDist[v], min_index = v;

        int u = min_index;
        visited[u] = 1;

        for (int v = 1; v <= N; v++) {
            if (!visited[v] && dist[u][v] && minDist[u] != INT_MAX &&
                minDist[u] + dist[u][v] < minDist[v] &&
                !排斥[culture[v]][culture[u]]) {
                minDist[v] = minDist[u] + dist[u][v];
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &N, &K, &M, &S, &T);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &culture[i]);
    }

    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= K; j++) {
            scanf("%d", &排斥[i][j]);
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            dist[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < M; i++) {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        if (dist[u][v] > d) {
            dist[u][v] = d;
            dist[v][u] = d;
        }
    }

    dijkstra();

    if (minDist[T] == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", minDist[T]);
    }

    return 0;
}