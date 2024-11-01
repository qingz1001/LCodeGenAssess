#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_K 100
#define INF 0x3f3f3f3f

int N, K, M, S, T;
int C[MAX_N];
int A[MAX_K][MAX_K];
int D[MAX_N][MAX_N];

void dijkstra(int start) {
    int dist[MAX_N];
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    for (int i = 0; i < N - 1; i++) {
        int u = -1;
        for (int j = 0; j < N; j++) {
            if (dist[j] != INF && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        for (int v = 0; v < N; v++) {
            if (D[u][v] != INF && dist[v] > dist[u] + D[u][v]) {
                dist[v] = dist[u] + D[u][v];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (A[C[start]][C[i]] == 1) {
            dist[i] = INF;
        }
    }

    printf("%d\n", dist[T]);
}

int main() {
    scanf("%d %d %d %d %d", &N, &K, &M, &S, &T);
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                D[i][j] = 0;
            } else {
                D[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < M; i++) {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        u--; v--;
        D[u][v] = D[v][u] = d;
    }

    dijkstra(S - 1);

    return 0;
}