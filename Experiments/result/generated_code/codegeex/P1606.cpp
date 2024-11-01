#include <stdio.h>
#include <stdlib.h>

#define MAXN 30

int m, n;
int pond[MAXN][MAXN];
int dist[MAXN][MAXN];
int dx[8] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[8] = {2, -2, 2, -2, 1, -1, 1, -1};
long long ways[MAXN][MAXN];
long long totalWays;

void bfs(int startX, int startY) {
    int visited[MAXN][MAXN] = {0};
    int queue[MAXN * MAXN][2];
    int front = 0, rear = 0;
    queue[rear][0] = startX;
    queue[rear++][1] = startY;
    visited[startX][startY] = 1;
    dist[startX][startY] = 0;
    ways[startX][startY] = 1;

    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front++][1];
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && pond[nx][ny] != 2 && !visited[nx][ny]) {
                visited[nx][ny] = 1;
                dist[nx][ny] = dist[x][y] + (pond[nx][ny] == 1 ? 0 : 1);
                ways[nx][ny] = ways[x][y] * (pond[nx][ny] == 1 ? 1 : 2);
                queue[rear][0] = nx;
                queue[rear++][1] = ny;
            }
        }
    }
}

int main() {
    scanf("%d%d", &m, &n);
    int startX, startY, endX, endY;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &pond[i][j]);
            if (pond[i][j] == 3) {
                startX = i;
                startY = j;
            } else if (pond[i][j] == 4) {
                endX = i;
                endY = j;
            }
            dist[i][j] = -1;
            ways[i][j] = 0;
        }
    }

    bfs(startX, startY);

    int minLilies = dist[endX][endY];
    if (minLilies == -1) {
        printf("-1\n");
    } else {
        printf("%d\n%lld\n", minLilies, ways[endX][endY]);
    }

    return 0;
}