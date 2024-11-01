#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 15

int m, n;
int maze[MAX_SIZE][MAX_SIZE];
int start_x, start_y;
int end_x, end_y;
int visited[MAX_SIZE][MAX_SIZE];

void dfs(int x, int y, char *path, int path_len) {
    if (x == end_x && y == end_y) {
        for (int i = 0; i < path_len; i++) {
            printf("%s", path + i);
        }
        printf("\n");
        return;
    }

    int directions[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    char direction_chars[4] = {'L', 'U', 'R', 'D'};

    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        if (new_x >= 0 && new_x < m && new_y >= 0 && new_y < n && maze[new_x][new_y] == 1 && !visited[new_x][new_y]) {
            visited[new_x][new_y] = 1;
            path[path_len] = '(';
            path[path_len + 1] = '0' + new_x;
            path[path_len + 2] = ',';
            path[path_len + 3] = '0' + new_y;
            path[path_len + 4] = ')';
            if (i > 0) {
                path[path_len + 5] = '-';
                path[path_len + 6] = '>';
                dfs(new_x, new_y, path, path_len + 7);
            } else {
                dfs(new_x, new_y, path, path_len + 5);
            }
            visited[new_x][new_y] = 0;
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

    char path[MAX_SIZE * MAX_SIZE * 2];
    path[0] = '\0';

    visited[start_x][start_y] = 1;
    dfs(start_x, start_y, path, 0);

    if (path[0] == '\0') {
        printf("-1\n");
    }

    return 0;
}