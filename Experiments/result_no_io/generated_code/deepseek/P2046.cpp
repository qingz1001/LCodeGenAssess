#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 501

int n;
int flow[4][MAXN][MAXN]; // 0: west to east, 1: north to south, 2: east to west, 3: south to north
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
            dist[i][j] = INT_MAX;
        }
    }
    dist[0][0] = 0;

    for (k = 0; k <= (n + 1) * (n + 1); k++) {
        int minDist = INT_MAX;
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
            dist[x + 1][y] = min(dist[x + 1][y], dist[x][y] + flow[1][x][y]);
        }
        if (x > 0) {
            dist[x - 1][y] = min(dist[x - 1][y], dist[x][y] + flow[3][x - 1][y]);
        }
        if (y < n) {
            dist[x][y + 1] = min(dist[x][y + 1], dist[x][y] + flow[0][x][y]);
        }
        if (y > 0) {
            dist[x][y - 1] = min(dist[x][y - 1], dist[x][y] + flow[2][x][y - 1]);
        }
    }
}

int main() {
    scanf("%d", &n);
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < n * (n + 1); j++) {
            scanf("%d", &flow[i][j / (n + 1)][j % (n + 1)]);
        }
    }

    dijkstra();

    printf("%d\n", dist[n][n]);
    return 0;
}