#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 182
#define MAX_M 182

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int screen[MAX_N][MAX_M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &screen[i][j]);
        }
    }

    int dist[MAX_N][MAX_M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (screen[i][j] == 1) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INT_MAX;
            }
        }
    }

    // BFS to find the shortest distance from each black pixel to the nearest white pixel
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (dist[i][j] == 0) {
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x >= 0 && x < N && y >= 0 && y < M && dist[x][y] > dist[i][j] + 1) {
                        dist[x][y] = dist[i][j] + 1;
                    }
                }
            }
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        for (int j = M - 1; j >= 0; j--) {
            if (dist[i][j] == 0) {
                for (int k = 0; k < 4; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x >= 0 && x < N && y >= 0 && y < M && dist[x][y] > dist[i][j] + 1) {
                        dist[x][y] = dist[i][j] + 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}