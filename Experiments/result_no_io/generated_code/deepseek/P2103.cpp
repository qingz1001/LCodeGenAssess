#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500
#define INF INT_MAX

int N, M;
int dist[MAXN][MAXN];
int count[MAXN][MAXN];

void floyd_warshall() {
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        count[i][j] = count[i][k] * count[k][j];
                    } else if (dist[i][j] == dist[i][k] + dist[k][j]) {
                        count[i][j] += count[i][k] * count[k][j];
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                dist[i][j] = 0;
                count[i][j] = 1;
            } else {
                dist[i][j] = INF;
                count[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < M; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        x--; y--;
        dist[x][y] = dist[y][x] = z;
        count[x][y] = count[y][x] = 1;
    }

    floyd_warshall();

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            printf("%d ", count[i][j]);
        }
    }
    printf("\n");

    return 0;
}