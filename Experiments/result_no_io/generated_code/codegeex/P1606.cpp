#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 30

int m, n;
int pond[MAXN + 1][MAXN + 1];
int dist[MAXN + 1][MAXN + 1];
long long ways[MAXN + 1][MAXN + 1];
int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

void bfs(int startX, int startY, int endX, int endY) {
    memset(dist, 0x3f, sizeof(dist));
    memset(ways, 0, sizeof(ways));
    dist[startX][startY] = 0;
    ways[startX][startY] = 1;

    struct {
        int x, y;
    } q[MAXN * MAXN + 1];
    int front = 0, rear = 0;
    q[rear++] = (struct {int x, y;}){startX, startY};

    while (front < rear) {
        struct {int x, y;} cur = q[front++];
        for (int i = 0; i < 8; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx < 1 || nx > m || ny < 1 || ny > n || pond[nx][ny] == 2) continue;
            int ndist = dist[cur.x][cur.y] + (pond[nx][ny] == 1 ? 0 : 1);
            if (ndist < dist[nx][ny]) {
                dist[nx][ny] = ndist;
                ways[nx][ny] = ways[cur.x][cur.y];
                q[rear++] = (struct {int x, y;}){nx, ny};
            } else if (ndist == dist[nx][ny]) {
                ways[nx][ny] += ways[cur.x][cur.y];
            }
        }
    }

    printf("%d\n%lld\n", dist[endX][endY], ways[endX][endY]);
}

int main() {
    scanf("%d%d", &m, &n);
    int startX, startY, endX, endY;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &pond[i][j]);
            if (pond[i][j] == 3) {
                startX = i;
                startY = j;
                pond[i][j] = 1;
            } else if (pond[i][j] == 4) {
                endX = i;
                endY = j;
                pond[i][j] = 1;
            }
        }
    }
    bfs(startX, startY, endX, endY);
    return 0;
}