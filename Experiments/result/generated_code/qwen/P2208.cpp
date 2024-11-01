#include <stdio.h>
#include <stdlib.h>

#define MAXN 501

int N, M;
char grid[MAXN][MAXN];
int visited[MAXN][MAXN][2];

int dx[] = {0, 0, 0, 1, -1};
int dy[] = {0, 1, -1, 0, 0};

int bfs(int startx, int starty) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            visited[i][j][0] = visited[i][j][1] = 0;
        }
    }

    int queue[2 * MAXN * MAXN][3];
    int front = 0, rear = 0;

    queue[rear][0] = startx;
    queue[rear++][1] = starty;
    queue[rear++][2] = 0;
    visited[startx][starty][0] = 1;

    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        int dir = queue[front++][2];

        if (grid[x][y] == 'D') {
            return dir;
        }

        for (int i = 0; i < 5; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < M && grid[nx][ny] != '#' && !visited[nx][ny][dir]) {
                visited[nx][ny][dir] = 1;
                queue[rear][0] = nx;
                queue[rear][1] = ny;
                queue[rear++][2] = dir;
            } else if (i == 3 || i == 4) {
                int new_dir = dir ^ 1;
                if (!visited[x][y][new_dir]) {
                    visited[x][y][new_dir] = 1;
                    queue[rear][0] = x;
                    queue[rear][1] = y;
                    queue[rear++][2] = new_dir;
                }
            }
        }
    }

    return -1;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; ++i) {
        scanf("%s", grid[i]);
    }

    int startx, starty;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'C') {
                startx = i;
                starty = j;
                break;
            }
        }
    }

    int result = bfs(startx, starty);
    printf("%d\n", result);

    return 0;
}