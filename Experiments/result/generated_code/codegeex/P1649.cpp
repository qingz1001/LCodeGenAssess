#include <stdio.h>
#include <string.h>

#define MAX_N 100

int n;
char grid[MAX_N][MAX_N];
int visited[MAX_N][MAX_N][4];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

struct Node {
    int x, y, direction, turns;
};

int bfs(int startX, int startY, int endX, int endY) {
    memset(visited, 0, sizeof(visited));
    struct Node queue[MAX_N * MAX_N * 2];
    int front = 0, rear = 0;

    queue[rear++] = (struct Node){startX, startY, -1, 0};
    visited[startX][startY][3] = 1; // Start facing any direction

    while (front < rear) {
        struct Node current = queue[front++];
        int x = current.x;
        int y = current.y;
        int dir = current.direction;
        int turns = current.turns;

        if (x == endX && y == endY) {
            return turns;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] != 'x') {
                if (visited[nx][ny][i] == 0) {
                    visited[nx][ny][i] = 1;
                    queue[rear++] = (struct Node){nx, ny, i, dir == -1 || dir == i ? turns : turns + 1};
                }
            }
        }
    }

    return -1;
}

int main() {
    scanf("%d", &n);
    int startX, startY, endX, endY;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == 'A') {
                startX = i;
                startY = j;
            } else if (grid[i][j] == 'B') {
                endX = i;
                endY = j;
            }
        }
    }

    int result = bfs(startX, startY, endX, endY);
    printf("%d\n", result);

    return 0;
}