#include <stdio.h>
#include <stdlib.h>

#define MAXN 1501
#define MAXM 1501

int n, m;
char maze[MAXN][MAXM];
int visited[MAXN][MAXM];

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void bfs(int startX, int startY) {
    int front = 0, rear = 0;
    int queue[MAXN * MAXM][2];
    queue[rear][0] = startX;
    queue[rear++][1] = startY;
    visited[startX][startY] = 1;

    while (front < rear) {
        int x = queue[front][0], y = queue[front++][1];
        for (int i = 0; i < 4; i++) {
            int nx = (x + dx[i]) % n;
            int ny = (y + dy[i]) % m;
            if (!isValid(nx, ny)) continue;
            if (maze[nx][ny] == '#' || visited[nx][ny]) continue;
            visited[nx][ny] = 1;
            queue[rear][0] = nx;
            queue[rear++][1] = ny;
        }
    }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%s", maze[i]);
        }

        int startX, startY;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (maze[i][j] == 'S') {
                    startX = i;
                    startY = j;
                    break;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                visited[i][j] = 0;
            }
        }

        bfs(startX, startY);

        int flag = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (visited[i][j] == 0 && maze[i][j] == '.') {
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }

        if (flag) {
            printf("No\n");
        } else {
            printf("Yes\n");
        }
    }
    return 0;
}