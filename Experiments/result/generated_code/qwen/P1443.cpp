#include <stdio.h>
#include <stdlib.h>

#define MAXN 405
#define INF 999999

int n, m, x, y;
int board[MAXN][MAXN];
int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};

void bfs() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            board[i][j] = INF;
        }
    }
    board[x][y] = 0;
    int queue[MAXN * MAXN][2], front = 0, rear = 0;
    queue[rear][0] = x, queue[rear++][1] = y;
    while (front != rear) {
        int cx = queue[front][0], cy = queue[front++][1];
        for (int k = 0; k < 8; ++k) {
            int nx = cx + dx[k], ny = cy + dy[k];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && board[nx][ny] == INF) {
                board[nx][ny] = board[cx][cy] + 1;
                queue[rear][0] = nx, queue[rear++][1] = ny;
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &x, &y);
    bfs();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    return 0;
}