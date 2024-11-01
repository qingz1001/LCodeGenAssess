#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1500
#define MAX_M 1500

char maze[MAX_N][MAX_M];
int n, m;
int start_x, start_y;

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && (maze[x % n][y % m] == '.' || maze[x % n][y % m] == 'S');
}

void dfs(int x, int y) {
    if (!is_valid(x, y)) return;
    maze[x % n][y % m] = '#'; // Mark as visited
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < n; ++i) {
            scanf(" %s", maze[i]);
            for (int j = 0; j < m; ++j) {
                if (maze[i][j] == 'S') {
                    start_x = i;
                    start_y = j;
                }
            }
        }

        dfs(start_x, start_y);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (maze[i][j] == '.') {
                    printf("Yes\n");
                    goto next_case;
                }
            }
        }
        printf("No\n");

        next_case:;
    }
    return 0;
}