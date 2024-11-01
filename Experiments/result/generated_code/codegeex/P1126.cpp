#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50
#define MAXM 50
#define MAX_DIR 4

typedef struct {
    int x, y, dir, steps;
} State;

int n, m;
int grid[MAXN][MAXM];
int visited[MAXN][MAXM][MAX_DIR];
int dist[MAXN][MAXM][MAX_DIR];

int dx[4] = {0, 1, 0, -1}; // East, South, West, North
int dy[4] = {1, 0, -1, 0};

int isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 0;
}

int bfs(int startX, int startY, int targetX, int targetY, char startDir) {
    int startDirInt;
    switch (startDir) {
        case 'E': startDirInt = 0; break;
        case 'S': startDirInt = 1; break;
        case 'W': startDirInt = 2; break;
        case 'N': startDirInt = 3; break;
    }

    State queue[2500];
    int front = 0, rear = 0;
    queue[rear++] = (State){startX, startY, startDirInt, 0};
    visited[startX][startY][startDirInt] = 1;
    dist[startX][startY][startDirInt] = 0;

    while (front < rear) {
        State current = queue[front++];
        int x = current.x, y = current.y, dir = current.dir, steps = current.steps;

        if (x == targetX && y == targetY) {
            return steps;
        }

        // Move forward by 1, 2, or 3 steps
        for (int i = 1; i <= 3; i++) {
            int nx = x + i * dx[dir];
            int ny = y + i * dy[dir];
            if (!isValid(nx, ny)) break;
            if (!visited[nx][ny][dir]) {
                visited[nx][ny][dir] = 1;
                dist[nx][ny][dir] = steps + i;
                queue[rear++] = (State){nx, ny, dir, steps + i};
            }
        }

        // Turn left
        int leftDir = (dir + 3) % MAX_DIR;
        if (!visited[x][y][leftDir]) {
            visited[x][y][leftDir] = 1;
            dist[x][y][leftDir] = steps + 1;
            queue[rear++] = (State){x, y, leftDir, steps + 1};
        }

        // Turn right
        int rightDir = (dir + 1) % MAX_DIR;
        if (!visited[x][y][rightDir]) {
            visited[x][y][rightDir] = 1;
            dist[x][y][rightDir] = steps + 1;
            queue[rear++] = (State){x, y, rightDir, steps + 1};
        }
    }

    return -1;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int startX, startY, targetX, targetY;
    char startDir;
    scanf("%d %d %d %d %c", &startX, &startY, &targetX, &targetY, &startDir);

    memset(visited, 0, sizeof(visited));
    memset(dist, 0, sizeof(dist));

    int result = bfs(startX, startY, targetX, targetY, startDir);
    printf("%d\n", result);

    return 0;
}