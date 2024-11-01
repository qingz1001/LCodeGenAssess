#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500
#define INF 0x3f3f3f3f

int dist[MAXN + 1][MAXN + 1];
int path[MAXN + 1][MAXN + 1];

void floyd(int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j && j != k && i != k) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        path[i][j] = path[i][k] * path[k][j];
                    } else if (dist[i][j] == dist[i][k] + dist[k][j]) {
                        path[i][j] += path[i][k] * path[k][j];
                    }
                }
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    memset(dist, INF, sizeof(dist));
    memset(path, 0, sizeof(path));

    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
        path[i][i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        dist[x][y] = z;
        dist[y][x] = z;
        path[x][y] = 1;
        path[y][x] = 1;
    }

    floyd(n);

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            printf("%d ", path[i][j]);
        }
    }
    printf("\n");

    return 0;
}