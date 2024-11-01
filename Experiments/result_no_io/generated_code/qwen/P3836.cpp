#include <stdio.h>
#include <stdlib.h>

#define MAXN 1024

char grid[MAXN][MAXN];
int m, n, k;

void dfs(int x, int y) {
    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != '.') return;
    grid[x][y] = 'X';
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    scanf("%d %d %d", &m, &n, &k);
    for (int i = 0; i < m; i++) {
        scanf("%s", grid[i]);
    }

    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '.' && (i == 0 || i == m - 1 || j == 0 || j == n - 1)) {
                dfs(i, j);
                count++;
            }
        }
    }

    while (count > k) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'X') {
                    grid[i][j] = '.';
                    break;
                }
            }
            if (grid[i][j] == 'X') break;
        }
        count--;
    }

    for (int i = 0; i < m; i++) {
        printf("%s\n", grid[i]);
    }

    return 0;
}