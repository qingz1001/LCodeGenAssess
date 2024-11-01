#include <stdio.h>
#include <stdlib.h>

#define MAXN 200
#define INF 10001

int N, M;
int graph[MAXN][MAXN];
int dist[MAXN][MAXN];

void floyd() {
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
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
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;
        graph[u][v] = w;
        graph[v][u] = w;
        dist[u][v] = w;
        dist[v][u] = w;
    }

    floyd();

    int important_cities = 0;
    for (int c = 0; c < N; c++) {
        int flag = 0;
        for (int a = 0; a < N; a++) {
            if (a != c) {
                for (int b = 0; b < N; b++) {
                    if (b != c && a != b) {
                        int original_dist = dist[a][b];
                        dist[a][b] = INF;
                        floyd();
                        if (dist[a][b] > original_dist || dist[a][b] == INF) {
                            flag = 1;
                            break;
                        }
                        dist[a][b] = original_dist;
                    }
                }
                if (flag) {
                    break;
                }
            }
        }
        if (flag) {
            printf("%d ", c + 1);
            important_cities++;
        }
    }

    if (!important_cities) {
        printf("No important cities.");
    }

    return 0;
}