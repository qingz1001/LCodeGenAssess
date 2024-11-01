#include <stdio.h>
#include <string.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[1001][1001];
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m - 3; j++) {
            if (grid[i][j] == 'h' && grid[i][j + 1] == 'e' && grid[i][j + 2] == 'h' && grid[i][j + 3] == 'e') {
                count++;
            }
        }
    }

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n - 3; i++) {
            if (grid[i][j] == 'h' && grid[i + 1][j] == 'e' && grid[i + 2][j] == 'h' && grid[i + 3][j] == 'e') {
                count++;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}