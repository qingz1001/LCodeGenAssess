#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50
#define INF 0x3f3f3f3f

int n, m;
int grid[MAXN][MAXN];
int dist[MAXN][MAXN][4];

int dx[4] = {0, 1, 0, -1}; // East, South, West, North
int dy[4] = {1, 0, -1, 0};

void printGrid() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

int getDir(char d) {
    if (d == 'E') return 0;
    if (d == 'S') return 1;
    if (d == 'W') return 2;
    if (d == 'N') return 3;
    return -1;
}

void bfs(int startX, int startY, int startDir) {
    memset(dist, INF, sizeof(dist));
    dist[startX][startY][startDir] = 0;
    int queue[MAXN * MAXN * 4][3];
    int front = 0, rear = 0;
    queue[rear][0] = startX;
    queue[rear][1] = startY;
    queue[rear++][2] = startDir;

    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        int dir = queue[front++][2];
        int steps = dist[x][y][dir];

        // Try all four directions
        for (int i = 0; i < 4; i++) {
            int newDir = (dir + i) % 4;
            int nx = x + dx[newDir];
            int ny = y + dy[newDir];

            // Check if the new position is within bounds and not blocked
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 0) {
                int newSteps = steps + 1;
                if (newSteps < dist[nx][ny][newDir]) {
                    dist[nx][ny][newDir] = newSteps;
                    queue[rear][0] = nx;
                    queue[rear][1] = ny;
                    queue[rear++][2] = newDir;
                }
            }
        }

        // Try to move 1, 2, or 3 steps forward
        for (int step = 1; step <= 3; step++) {
            int nx = x + step * dx[dir];
            int ny = y + step * dy[dir];

            // Check if the new position is within bounds and not blocked
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 0) {
                int newSteps = steps + 1;
                if (newSteps < dist[nx][ny][dir]) {
                    dist[nx][ny][dir] = newSteps;
                    queue[rear][0] = nx;
                    queue[rear][1] = ny;
                    queue[rear++][2] = dir;
                }
            } else {
                break;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int startX, startY, endX, endY;
    char startDir, endDir;
    scanf("%d%d%d%d %c", &startX, &startY, &endX, &endY, &startDir);

    bfs(startX, startY, getDir(startDir));

    int minTime = INF;
    for (int i = 0; i < 4; i++) {
        minTime = (minTime < dist[endX][endY][i]) ? minTime : dist[endX][endY][i];
    }

    if (minTime == INF) {
        printf("-1\n");
    } else {
        printf("%d\n", minTime);
    }

    return 0;
}