#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200
#define MAXM 19900
#define MAXQ 50000

int N, M, Q;
int t[MAXN];
int dist[MAXN][MAXN];
int queries[MAXQ][3];

void floyd_warshall() {
    for (int k = 0; k < N; k++) {
        if (t[k] == 0) continue;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
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
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        dist[u][v] = w;
        dist[v][u] = w;
    }

    floyd_warshall();

    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);
        if (t < t[x] || t < t[y] || dist[x][y] == INT_MAX) {
            printf("-1\n");
        } else {
            printf("%d\n", dist[x][y]);
        }
    }

    return 0;
}