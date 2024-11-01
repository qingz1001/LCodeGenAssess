#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

int N;
char grid[MAXN][MAXN];
int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int bfs(int startX, int startY, int endX, int endY) {
    int queue[MAXN * MAXN][2];
    int front = 0, rear = 0;
    int visited[MAXN][MAXN][4] = {0}; // visited[x][y][dir]: 0=up, 1=right, 2=down, 3=left
    queue[rear][0] = startX;
    queue[rear++][1] = startY;
    visited[startX][startY][0] = 1;

    while (front != rear) {
        int x = queue[front][0];
        int y = queue[front++][1];
        int dir = (visited[x][y][0] + 1) % 4; // Next direction to try

        for (int i = 0; i < 4; i++) {
            int nx = x + directions[(i + dir) % 4][0];
            int ny = y + directions[(i + dir) % 4][1];

            if (nx >= 0 && nx < N && ny >= 0 && ny < N && grid[nx][ny] != 'x') {
                if (nx == endX && ny == endY) {
                    return visited[x][y][(i + dir) % 4];
                }
                if (!visited[nx][ny][(i + dir) % 4]) {
                    visited[nx][ny][(i + dir) % 4] = visited[x][y][(i + dir) % 4] + 1;
                    queue[rear][0] = nx;
                    queue[rear++][1] = ny;
                }
            }
        }
    }

    return -1;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %c", &grid[i][j]);
        }
    }

    int startX, startY, endX, endY;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 'A') {
                startX = i;
                startY = j;
            } else if (grid[i][j] == 'B') {
                endX = i;
                endY = j;
            }
        }
    }

    int minTurns = bfs(startX, startY, endX, endY);
    printf("%d\n", minTurns);

    return 0;
}