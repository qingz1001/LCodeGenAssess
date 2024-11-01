#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 50
#define MAXM 50

typedef struct {
    int x, y, dir, time;
} State;

int N, M;
int grid[MAXN][MAXM];
int visited[MAXN][MAXM][4];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
char dir_map[] = {'E', 'S', 'W', 'N'};

int bfs(int sx, int sy, int ex, int ey, int start_dir) {
    int dir_index = strchr(dir_map, start_dir) - dir_map;
    State init = {sx, sy, dir_index, 0};
    memset(visited, 0, sizeof(visited));
    visited[sx][sy][dir_index] = 1;

    State queue[MAXN * MAXM * 4];
    int front = 0, rear = 0;
    queue[rear++] = init;

    while (front < rear) {
        State curr = queue[front++];
        if (curr.x == ex && curr.y == ey) {
            return curr.time;
        }

        // Move forward 1, 2, 3 steps
        for (int step = 1; step <= 3; step++) {
            int nx = curr.x + step * dx[curr.dir];
            int ny = curr.y + step * dy[curr.dir];
            if (nx < 0 || nx >= N || ny < 0 || ny >= M || grid[nx][ny] == 1) break;
            if (visited[nx][ny][curr.dir]) continue;
            visited[nx][ny][curr.dir] = 1;
            queue[rear++] = (State){nx, ny, curr.dir, curr.time + 1};
        }

        // Turn left
        int left_dir = (curr.dir + 3) % 4;
        if (!visited[curr.x][curr.y][left_dir]) {
            visited[curr.x][curr.y][left_dir] = 1;
            queue[rear++] = (State){curr.x, curr.y, left_dir, curr.time + 1};
        }

        // Turn right
        int right_dir = (curr.dir + 1) % 4;
        if (!visited[curr.x][curr.y][right_dir]) {
            visited[curr.x][curr.y][right_dir] = 1;
            queue[rear++] = (State){curr.x, curr.y, right_dir, curr.time + 1};
        }
    }

    return -1;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int sx, sy, ex, ey;
    char start_dir;
    scanf("%d %d %d %d %c", &sx, &sy, &ex, &ey, &start_dir);

    // Convert to 0-based index
    sx--; sy--; ex--; ey--;

    int result = bfs(sx, sy, ex, ey, start_dir);
    printf("%d\n", result);

    return 0;
}