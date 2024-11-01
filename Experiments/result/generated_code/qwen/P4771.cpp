#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 1000000000

int n, m, k;
int h[MAXN][MAXN];
int babingbabooms[MAXN];

void bfs(int start_x, int start_y, int *dist) {
    int queue[MAXN * MAXN];
    int front = 0, rear = 0;
    queue[rear++] = start_x * m + start_y;
    dist[start_x * m + start_y] = 0;

    while (front < rear) {
        int u = queue[front++];
        int x = u / m, y = u % m;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    if (abs(dx) + abs(dy) == 1 && h[nx][ny] < h[x][y]) {
                        if (dist[u] + 1 < dist[nx * m + ny]) {
                            dist[nx * m + ny] = dist[u] + 1;
                            queue[rear++] = nx * m + ny;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &h[i][j]);
        }
    }
    for (int i = 0; i < k; i++) {
        scanf("%d%d", &bapingbabooms[i], &babingbabooms[k + i]);
        babingbabooms[i]--;
        babingbabooms[k + i]--;
    }

    int result[MAXN * MAXN];
    for (int i = 0; i < n * m; i++) {
        result[i] = INF;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0) {
                result[i * m + j] = 0;
            } else {
                bfs(i, j, result);
            }
        }
    }

    for (int i = 0; i < k; i++) {
        int x = babingbabooms[i], y = babingbabooms[k + i];
        if (result[y * m + x] == INF) {
            printf("Pool Babingbaboom!\n");
        } else {
            printf("%d\n", result[y * m + x]);
        }
    }

    return 0;
}