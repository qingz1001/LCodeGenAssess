#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 500
#define MAXM 500

typedef struct {
    int x, y, flips, gravity;
} State;

char grid[MAXN][MAXM];
int dist[MAXN][MAXM][2];
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
int N, M;

int isValid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < M && grid[x][y] != '#';
}

int bfs(int sx, int sy, int ex, int ey) {
    State queue[MAXN * MAXM * 2];
    int front = 0, rear = 0;
    memset(dist, -1, sizeof(dist));

    queue[rear++] = (State){sx, sy, 0, 0};
    dist[sx][sy][0] = 0;

    while (front < rear) {
        State cur = queue[front++];
        int x = cur.x, y = cur.y, flips = cur.flips, gravity = cur.gravity;

        if (x == ex && y == ey) return flips;

        // Fall down if possible
        int nx = x, ny = y;
        if (gravity == 0) {
            while (nx + 1 < N && grid[nx + 1][ny] != '#') nx++;
        } else {
            while (nx - 1 >= 0 && grid[nx - 1][ny] != '#') nx--;
        }
        if (dist[nx][ny][gravity] == -1 || dist[nx][ny][gravity] > flips) {
            dist[nx][ny][gravity] = flips;
            queue[rear++] = (State){nx, ny, flips, gravity};
        }

        // Move left or right
        for (int i = 0; i < 2; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (isValid(nx, ny) && (dist[nx][ny][gravity] == -1 || dist[nx][ny][gravity] > flips)) {
                dist[nx][ny][gravity] = flips;
                queue[rear++] = (State){nx, ny, flips, gravity};
            }
        }

        // Flip gravity
        int newGravity = 1 - gravity;
        if (dist[x][y][newGravity] == -1 || dist[x][y][newGravity] > flips + 1) {
            dist[x][y][newGravity] = flips + 1;
            queue[rear++] = (State){x, y, flips + 1, newGravity};
        }
    }

    return -1;
}

int main() {
    scanf("%d %d", &N, &M);
    int sx = -1, sy = -1, ex = -1, ey = -1;

    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'C') {
                sx = i; sy = j;
            } else if (grid[i][j] == 'D') {
                ex = i; ey = j;
            }
        }
    }

    if (sx == -1 || sy == -1 || ex == -1 || ey == -1) {
        printf("-1\n");
        return 0;
    }

    int result = bfs(sx, sy, ex, ey);
    printf("%d\n", result);

    return 0;
}