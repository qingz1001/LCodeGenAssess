#include <stdio.h>

int maze[15][15];
int start_x, start_y, end_x, end_y;
int path[100][3]; // 存储路径，path[i][0]为x坐标，path[i][1]为y坐标，path[i][2]为方向
int path_len = 0;
int found = 0;

void print_path() {
    printf("(%d,%d)", path[0][0], path[0][1]);
    for (int i = 1; i < path_len; i++) {
        printf("->(%d,%d)", path[i][0], path[i][1]);
    }
    printf("\n");
}

void dfs(int x, int y) {
    if (x == end_x && y == end_y) {
        found = 1;
        print_path();
        return;
    }
    if (x < 0 || x >= 15 || y < 0 || y >= 15 || maze[x][y] == 0) {
        return;
    }
    maze[x][y] = 0; // 标记为已访问
    path[path_len][0] = x;
    path[path_len][1] = y;
    path[path_len][2] = 0; // 0表示左
    path_len++;
    dfs(x, y - 1); // 左
    path_len--;
    path[path_len][0] = x;
    path[path_len][1] = y;
    path[path_len][2] = 1; // 1表示上
    path_len++;
    dfs(x - 1, y); // 上
    path_len--;
    path[path_len][0] = x;
    path[path_len][1] = y;
    path[path_len][2] = 2; // 2表示右
    path_len++;
    dfs(x, y + 1); // 右
    path_len--;
    path[path_len][0] = x;
    path[path_len][1] = y;
    path[path_len][2] = 3; // 3表示下
    path_len++;
    dfs(x + 1, y); // 下
    path_len--;
    maze[x][y] = 1; // 恢复未访问状态
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    scanf("%d %d", &start_x, &start_y);
    scanf("%d %d", &end_x, &end_y);
    dfs(start_x, start_y);
    if (!found) {
        printf("-1\n");
    }
    return 0;
}