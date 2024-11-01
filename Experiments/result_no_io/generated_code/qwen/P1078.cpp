#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_K 100
#define INF 1000000

int N, K, M, S, T;
int C[MAX_N];
int A[MAX_K][MAX_K];
int D[MAX_N][MAX_N];

void floyd() {
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (D[i][k] != INF && D[k][j] != INF) {
                    D[i][j] = D[i][j] < D[i][k] + D[k][j] ? D[i][j] : D[i][k] + D[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &N, &K, &M, &S, &T);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &C[i]);
    }
    for (int i = 1; i <= K; i++) {
        for (int j = 1; j <= K; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j) {
                D[i][j] = 0;
            } else {
                D[i][j] = INF;
            }
        }
    }
    for (int i = 1; i <= M; i++) {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        D[u][v] = D[v][u] = d;
    }
    floyd();
    int min_dist = INF;
    for (int i = 1; i <= N; i++) {
        if (A[C[S]][C[i]] == 0 && A[C[i]][C[T]] == 0) {
            min_dist = min_dist < D[S][i] + D[i][T] ? min_dist : D[S][i] + D[i][T];
        }
    }
    if (min_dist == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", min_dist);
    }
    return 0;
}