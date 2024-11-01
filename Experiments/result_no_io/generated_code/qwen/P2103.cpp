#include <stdio.h>
#include <stdlib.h>

#define MAXN 505
#define INF 0x3f3f3f3f

int n, m;
int graph[MAXN][MAXN];
int dist[MAXN][MAXN];

void floyd() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }

    int x, y, z;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &x, &y, &z);
        graph[x][y] = graph[y][x] = z;
        dist[x][y] = dist[y][x] = z;
    }

    floyd();

    int count[MAXN][MAXN] = {0};
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] + dist[k][j] == dist[i][j]) {
                    count[i][j]++;
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            printf("%d ", count[i][j]);
        }
    }
    printf("\n");

    return 0;
}