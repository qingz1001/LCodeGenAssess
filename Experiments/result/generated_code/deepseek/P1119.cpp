#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200
#define MAXM 19900
#define INF INT_MAX

typedef struct {
    int u, v, w;
} Edge;

int N, M;
int t[MAXN];
Edge edges[MAXM];
int dist[MAXN][MAXN];

void floyd_warshall() {
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &t[i]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
        dist[u][v] = dist[v][u] = w;
    }

    floyd_warshall();

    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);
        if (t < t[x] || t < t[y]) {
            printf("-1\n");
        } else {
            if (dist[x][y] == INF) {
                printf("-1\n");
            } else {
                printf("%d\n", dist[x][y]);
            }
        }
    }

    return 0;
}