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
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int min(int a, int b) {
    return a < b ? a : b;
}

int bfs(int sx, int sy, int ex, int ey) {
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
        queue[rear++] = (State){sx, sy, i, 0};
        visited[sx][sy][i] = 0;
    }

    while (front < rear) {
        State current = queue[front++];
        int x = current.x, y = current.y, dir = current.dir, turns = current.turns;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            int nturns = turns + (i != dir);

            if (nx >= 0 && nx < N && ny >= 0 && ny < N && grid[nx][ny] != 'x' && nturns < visited[nx][ny][i]) {
                visited[nx][ny][i] = nturns;
                queue[rear++] = (State){nx, ny, i, nturns};
            }
        }
    }

    int minTurns = INT_MAX;
    for (int i = 0; i < 4; i++) {
        minTurns = min(minTurns, visited[ex][ey][i]);
    }

    return minTurns == INT_MAX ? -1 : minTurns;
}

int main() {
    scanf("%d", &N);
    int sx = -1, sy = -1, ex = -1, ey = -1;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == 'A') {
                sx = i;
                sy = j;
            } else if (grid[i][j] == 'B') {
                ex = i;
                ey = j;
            }
        }
    }

    int result = bfs(sx, sy, ex, ey);
    printf("%d\n", result);

    return 0;
}