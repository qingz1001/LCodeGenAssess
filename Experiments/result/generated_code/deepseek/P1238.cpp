#include <stdio.h>
#include <stdlib.h>

#define MAX 15

int m, n;
int maze[MAX][MAX];
int start_x, start_y, end_x, end_y;
int visited[MAX][MAX];
int directions[4][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} }; // 左上右下

void printPath(int path[][2], int len) {
    for (int i = 0; i < len; i++) {
        if (i == 0) {
            printf("(%d,%d)", path[i][0], path[i][1]);
        } else {
            printf("->(%d,%d)", path[i][0], path[i][1]);
        }
    }
    printf("\n");
}

void dfs(int x, int y, int path[][2], int len) {
    if (x == end_x && y == end_y) {
        printPath(path, len);
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];

        if (nx >= 0 && nx < m && ny >= 0 && ny < n && maze[nx][ny] == 1 && !visited[nx][ny]) {
            visited[nx][ny] = 1;
            path[len][0] = nx + 1;
            path[len][1] = ny + 1;
            dfs(nx, ny, path, len + 1);
            visited[nx][ny] = 0;
        }
    }
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    scanf("%d %d", &start_x, &start_y);
    scanf("%d %d", &end_x, &end_y);

    start_x--; start_y--; end_x--; end_y--;

    if (maze[start_x][start_y] == 0 || maze[end_x][end_y] == 0) {
        printf("-1\n");
        return 0;
    }

    int path[MAX * MAX][2];
    path[0][0] = start_x + 1;
    path[0][1] = start_y + 1;
    visited[start_x][start_y] = 1;

    dfs(start_x, start_y, path, 1);

    int found = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i][j] == 1) {
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("-1\n");
    }

    return 0;
}