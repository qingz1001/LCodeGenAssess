#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 501
#define INF 0x3f3f3f3f

int dist[MAX_N][MAX_N];
int count[MAX_N][MAX_N];
int n, m;

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    count[i][j] = count[i][k] * count[k][j];
                } else if (dist[i][k] + dist[k][j] == dist[i][j]) {
                    count[i][j] += count[i][k] * count[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    memset(dist, 0x3f, sizeof(dist));
    memset(count, 0, sizeof(count));

    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
        count[i][i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        dist[x][y] = dist[y][x] = z;
        count[x][y] = count[y][x] = 1;
    }

    floyd();

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            printf("%d ", count[i][j]);
        }
    }

    return 0;
}