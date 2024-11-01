#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200
#define INF INT_MAX

int N, M;
int graph[MAXN][MAXN];
int dist[MAXN][MAXN];
int important[MAXN];

void floyd_warshall() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = graph[i][j];
        }
    }

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
        for (int j = 0; j < N; j++) {
            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INF;
        }
    }

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;
        graph[u][v] = graph[v][u] = w;
    }

    floyd_warshall();

    for (int c = 0; c < N; c++) {
        for (int a = 0; a < N; a++) {
            for (int b = 0; b < N; b++) {
                if (a != b && a != c && b != c && dist[a][c] != INF && dist[c][b] != INF) {
                    if (dist[a][b] > dist[a][c] + dist[c][b]) {
                        important[c] = 1;
                    }
                }
            }
        }
    }

    int found = 0;
    for (int i = 0; i < N; i++) {
        if (important[i]) {
            if (found) printf(" ");
            printf("%d", i + 1);
            found = 1;
        }
    }

    if (!found) {
        printf("No important cities.");
    }

    printf("\n");

    return 0;
}