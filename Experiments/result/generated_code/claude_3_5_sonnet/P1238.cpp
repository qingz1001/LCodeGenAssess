#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 15

int m, n;
int maze[MAX_SIZE][MAX_SIZE];
int start_x, start_y, end_x, end_y;
int path[MAX_SIZE * MAX_SIZE][2];
int path_length;
bool visited[MAX_SIZE][MAX_SIZE];
bool found_path;

int dx[] = {0, -1, 0, 1};  // 左上右下
int dy[] = {-1, 0, 1, 0};

void dfs(int x, int y) {
    if (x == end_x && y == end_y) {
        found_path = true;
        for (int i = 0; i < path_length; i++) {
            printf("(%d,%d)", path[i][0], path[i][1]);
            if (i < path_length - 1) {
                printf("->");
            }
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 1 && nx <= m && ny >= 1 && ny <= n && maze[nx][ny] == 1 && !visited[nx][ny]) {
            visited[nx][ny] = true;
            path[path_length][0] = nx;
            path[path_length][1] = ny;
            path_length++;

            dfs(nx, ny);

            visited[nx][ny] = false;
            path_length--;
        }
    }
}

int main() {
    scanf("%d %d", &m, &n);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    scanf("%d %d", &start_x, &start_y);
    scanf("%d %d", &end_x, &end_y);

    path[0][0] = start_x;
    path[0][1] = start_y;
    path_length = 1;
    visited[start_x][start_y] = true;

    dfs(start_x, start_y);

    if (!found_path) {
        printf("-1\n");
    }

    return 0;
}