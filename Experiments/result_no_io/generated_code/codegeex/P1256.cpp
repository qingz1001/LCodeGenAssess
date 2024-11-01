#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 182
#define MAXM 182
#define MAXN2 32852

int screen[MAXN][MAXM];
int dist[MAXN][MAXM];
int n, m;

void bfs(int startX, int startY) {
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int x, y, nx, ny;
    int front = 0, rear = 0;
    int queue[MAXN2][2];

    queue[rear][0] = startX;
    queue[rear][1] = startY;
    rear = (rear + 1) % MAXN2;
    dist[startX][startY] = 0;

    while (front != rear) {
        x = queue[front][0];
        y = queue[front][1];
        front = (front + 1) % MAXN2;

        for (int i = 0; i < 4; i++) {
            nx = x + dx[i];
            ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                queue[rear][0] = nx;
                queue[rear][1] = ny;
                rear = (rear + 1) % MAXN2;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &screen[i][j]);
            dist[i][j] = -1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (screen[i][j] == 1) {
                bfs(i, j);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    return 0;
}