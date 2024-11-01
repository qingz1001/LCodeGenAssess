#include <stdio.h>
#include <stdlib.h>

#define MAXN 405
#define INF 0x3f3f3f3f

int n, m, x, y;
int dist[MAXN][MAXN];
int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

void bfs() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dist[i][j] = INF;
        }
    }
    dist[x][y] = 0;
    int queue[MAXN * MAXN], front = 0, rear = 0;
    queue[rear++] = x * m + y;
    while (front != rear) {
        int u = queue[front++];
        int ux = u / m + 1, uy = u % m + 1;
        for (int k = 0; k < 8; k++) {
            int vx = ux + dx[k], vy = uy + dy[k];
            if (vx >= 1 && vx <= n && vy >= 1 && vy <= m && dist[vx][vy] == INF) {
                dist[vx][vy] = dist[ux][uy] + 1;
                queue[rear++] = vx * m + vy;
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &x, &y);
    bfs();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
    return 0;
}