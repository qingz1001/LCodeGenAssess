#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 501
#define INF INT_MAX

int n;
int flow[4 * MAXN * (MAXN + 1)];
int dist[MAXN][MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void dijkstra() {
    int i, j, k;
    int visited[MAXN][MAXN] = {0};
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= n; j++) {
            dist[i][j] = INF;
        }
    }
    dist[0][0] = 0;

    for (k = 0; k <= n * n; k++) {
        int minDist = INF;
        int x = -1, y = -1;
        for (i = 0; i <= n; i++) {
            for (j = 0; j <= n; j++) {
                if (!visited[i][j] && dist[i][j] < minDist) {
                    minDist = dist[i][j];
                    x = i;
                    y = j;
                }
            }
        }
        if (x == -1) break;
        visited[x][y] = 1;

        if (x < n) {
            dist[x + 1][y] = min(dist[x + 1][y], dist[x][y] + flow[2 * n * (n + 1) + x * (n + 1) + y]);
        }
        if (x > 0) {
            dist[x - 1][y] = min(dist[x - 1][y], dist[x][y] + flow[n * (n + 1) + x * (n + 1) + y]);
        }
        if (y < n) {
            dist[x][y + 1] = min(dist[x][y + 1], dist[x][y] + flow[x * (n + 1) + y]);
        }
        if (y > 0) {
            dist[x][y - 1] = min(dist[x][y - 1], dist[x][y] + flow[3 * n * (n + 1) + x * (n + 1) + y]);
        }
    }
}

int main() {
    scanf("%d", &n);
    int i;
    for (i = 0; i < 4 * n * (n + 1); i++) {
        scanf("%d", &flow[i]);
    }

    dijkstra();

    printf("%d\n", dist[n][n]);

    return 0;
}