#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100

typedef struct {
    int x, y, dir, turns;
} State;

int N;
char grid[MAXN][MAXN];
int visited[MAXN][MAXN][4];
int dx[] = {-1, 0, 1, 0}; // 上 右 下 左
int dy[] = {0, 1, 0, -1};

int min(int a, int b) {
    return a < b ? a : b;
}

int bfs(int startX, int startY, int endX, int endY) {
    State queue[MAXN * MAXN * 4];
    int front = 0, rear = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 4; k++) {
                visited[i][j][k] = INT_MAX;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        queue[rear++] = (State){startX, startY, i, 0};
        visited[startX][startY][i] = 0;
    }

    while (front < rear) {
        State current = queue[front++];

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            int nturns = current.turns + (current.dir != i);

            if (nx >= 0 && nx < N && ny >= 0 && ny < N && grid[nx][ny] != 'x' && nturns < visited[nx][ny][i]) {
                visited[nx][ny][i] = nturns;
                queue[rear++] = (State){nx, ny, i, nturns};
            }
        }
    }

    int minTurns = INT_MAX;
    for (int i = 0; i < 4; i++) {
        minTurns = min(minTurns, visited[endX][endY][i]);
    }

    return minTurns == INT_MAX ? -1 : minTurns;
}

int main() {
    scanf("%d", &N);
    int startX = -1, startY = -1, endX = -1, endY = -1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
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