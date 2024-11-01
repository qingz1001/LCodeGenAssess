#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 15

int m, n;
int maze[MAX_SIZE][MAX_SIZE];
int start_x, start_y, end_x, end_y;
int path[MAX_SIZE * MAX_SIZE];
int path_length = 0;

void print_path() {
    for (int i = 0; i < path_length; i++) {
        printf("(%d,%d)", path[i] / n, path[i] % n);
        if (i != path_length - 1) {
            printf("->");
        }
    }
    printf("\n");
}

int is_valid(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n && maze[x][y] == 1;
}

void dfs(int x, int y) {
    if (!is_valid(x, y)) {
        return;
    }
    if (x == end_x && y == end_y) {
        path[path_length++] = x * n + y;
        print_path();
        path_length--;
        return;
    }
    maze[x][y] = 0;
    path[path_length++] = x * n + y;
    dfs(x, y - 1); // Left
    dfs(x, y + 1); // Right
    dfs(x - 1, y); // Up
    dfs(x + 1, y); // Down
    maze[x][y] = 1;
    path_length--;
}

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    scanf("%d%d", &start_x, &start_y);
    scanf("%d%d", &end_x, &end_y);

    dfs(start_x, start_y);

    if (path_length == 0) {
        printf("-1\n");
    }

    return 0;
}