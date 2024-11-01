#include <stdio.h>

int main() {
    int n, m, c;
    scanf("%d %d %d", &n, &m, &c);
    int p[c];
    for (int i = 0; i < c; i++) {
        scanf("%d", &p[i]);
    }

    int grid[n][m];
    int color_index = 0;
    int count = 0;

    // Fill the grid with colors
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++) {
                grid[i][j] = color_index + 1;
                count++;
                if (count == p[color_index]) {
                    count = 0;
                    color_index++;
                }
            }
        } else {
            for (int j = m - 1; j >= 0; j--) {
                grid[i][j] = color_index + 1;
                count++;
                if (count == p[color_index]) {
                    count = 0;
                    color_index++;
                }
            }
        }
    }

    // Output the grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}