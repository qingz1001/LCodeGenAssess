#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 500
#define INF 1000000000

int N, M;
int dist[MAX_N][MAX_N];
int paths[MAX_N][MAX_N];

void floyd_warshall() {
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    paths[i][j] = 1;
                } else if (dist[i][k] + dist[k][j] == dist[i][j]) {
                    paths[i][j]++;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dist[i][j] = (i == j) ? 0 : INF;
            paths[i][j] = (i == j) ? 1 : 0;
        }
    }

    for (int i = 0; i < M; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        x--; y--;
        dist[x][y] = dist[y][x] = z;
        paths[x][y] = paths[y][x] = 1;
    }

    floyd_warshall();

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            printf("%d ", paths[i][j]);
        }
    }
    printf("\n");

    return 0;
}