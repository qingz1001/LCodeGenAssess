#include <stdio.h>
#include <string.h>

char grid[101][101];
int n;

void mark(int x, int y, int dx, int dy) {
    char *word = "yizhong";
    int i, j;
    for (i = 0; i < 7; i++) {
        if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] != word[i]) {
            return;
        }
        x += dx;
        y += dy;
    }
    x -= dx * 6;
    y -= dy * 6;
    for (i = 0; i < 7; i++) {
        grid[x][y] = word[i];
        x += dx;
        y += dy;
    }
}

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (grid[i][j] == 'y') {
                mark(i - 1, j - 1, -1, -1);
                mark(i - 1, j, -1, 0);
                mark(i - 1, j + 1, -1, 1);
                mark(i, j - 1, 0, -1);
                mark(i, j + 1, 0, 1);
                mark(i + 1, j - 1, 1, -1);
                mark(i + 1, j, 1, 0);
                mark(i + 1, j + 1, 1, 1);
            }
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (grid[i][j] != 'y' && grid[i][j] != 'i' && grid[i][j] != 'z' && grid[i][j] != 'h' && grid[i][j] != 'o' && grid[i][j] != 'n' && grid[i][j] != 'g') {
                grid[i][j] = '*';
            }
        }
    }

    for (i = 0; i < n; i++) {
        printf("%s\n", grid[i]);
    }

    return 0;
}