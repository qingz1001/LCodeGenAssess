#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAXN 50
#define MAXM 50

typedef struct {
    int x, y, dir;
} State;

int N, M;
int grid[MAXN][MAXM];
int startX, startY, endX, endY;
char startDir;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
char dir[] = {'E', 'S', 'W', 'N'};

int bfs() {
    int dist[MAXN][MAXM][4];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < 4; k++) {
                dist[i][j][k] = INT_MAX;
            }
        }
    }

    int startDirIndex;
    for (int i = 0; i < 4; i++) {
        if (dir[i] == startDir) {
            startDirIndex = i;
            break;
        }
    }

    State queue[MAXN * MAXM * 4];
    int front = 0, rear = 0;
    queue[rear++] = (State){startX, startY, startDirIndex};
    dist[startX][startY][startDirIndex] = 0;

    while (front < rear) {
        State current = queue[front++];
        int x = current.x, y = current.y, d = current.dir;
        int currentDist = dist[x][y][d];

        // Move forward 1, 2, 3 steps
        for (int step = 1; step <= 3; step++) {
            int nx = x + step * dx[d];
            int ny = y + step * dy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= M || grid[nx][ny] == 1) break;
            if (dist[nx][ny][d] > currentDist + 1) {
                dist[nx][ny][d] = currentDist + 1;
                queue[rear++] = (State){nx, ny, d};
            }
        }

        // Turn left
        int leftDir = (d + 3) % 4;
        if (dist[x][y][leftDir] > currentDist + 1) {
            dist[x][y][leftDir] = currentDist + 1;
            queue[rear++] = (State){x, y, leftDir};
        }

        // Turn right
        int rightDir = (d + 1) % 4;
        if (dist[x][y][rightDir] > currentDist + 1) {
            dist[x][y][rightDir] = currentDist + 1;
            queue[rear++] = (State){x, y, rightDir};
        }
    }

    int minTime = INT_MAX;
    for (int i = 0; i < 4; i++) {
        if (dist[endX][endY][i] < minTime) {
            minTime = dist[endX][endY][i];
        }
    }

    return minTime == INT_MAX ? -1 : minTime;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    scanf("%d %d %d %d %c", &startX, &startY, &endX, &endY, &startDir);

    int result = bfs();
    printf("%d\n", result);

    return 0;
}