#include <stdio.h>
#include <stdlib.h>

#define MAXN 21
#define MAXC 51

int n, m, c;
int p[MAXC];
int grid[MAXN][MAXN];

void printGrid() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

void dfs(int x, int y, int color) {
    if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] != 0) return;
    grid[x][y] = color;
    dfs(x - 1, y, color);
    dfs(x + 1, y, color);
    dfs(x, y - 1, color);
    dfs(x, y + 1, color);
}

int main() {
    scanf("%d %d %d", &n, &m, &c);
    for (int i = 0; i < c; i++) {
        scanf("%d", &p[i]);
    }

    int index = 0;
    for (int i = 0; i < c; i++) {
        while (p[i]--) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    if (grid[j][k] == 0) {
                        grid[j][k] = index + 1;
                        dfs(j, k, index + 1);
                        break;
                    }
                }
                if (grid[j][k] != 0) break;
            }
            if (grid[j][k] != 0) break;
            index++;
        }
    }

    printGrid();
    return 0;
}