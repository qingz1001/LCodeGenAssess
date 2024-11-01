#include <stdio.h>
#include <stdbool.h>

#define MAXN 30

int n, m;
char grid[MAXN][MAXN];
int count = 0;

bool is_valid(int x, int y, int dx, int dy) {
    if (x + dx >= n || y + dy >= m || x + dx < 0 || y + dy < 0) return false;
    if (grid[x][y] != '.' || grid[x + dx][y] != '.' || grid[x][y + dy] != '.') return false;
    return true;
}

void place_L(int x, int y, int dx, int dy) {
    grid[x][y] = '#';
    grid[x + dx][y] = '#';
    grid[x][y + dy] = '#';
}

void remove_L(int x, int y, int dx, int dy) {
    grid[x][y] = '.';
    grid[x + dx][y] = '.';
    grid[x][y + dy] = '.';
}

void dfs(int placed) {
    if (placed == 3) {
        count++;
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                if (is_valid(i, j, 1, 1)) {
                    place_L(i, j, 1, 1);
                    dfs(placed + 1);
                    remove_L(i, j, 1, 1);
                }
                if (is_valid(i, j, 1, 2)) {
                    place_L(i, j, 1, 2);
                    dfs(placed + 1);
                    remove_L(i, j, 1, 2);
                }
                if (is_valid(i, j, 2, 1)) {
                    place_L(i, j, 2, 1);
                    dfs(placed + 1);
                    remove_L(i, j, 2, 1);
                }
                if (is_valid(i, j, 2, 2)) {
                    place_L(i, j, 2, 2);
                    dfs(placed + 1);
                    remove_L(i, j, 2, 2);
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    dfs(0);
    printf("%d\n", count);

    return 0;
}