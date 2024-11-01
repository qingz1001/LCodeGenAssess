#include <stdio.h>

int main() {
    int n, m, c;
    scanf("%d %d %d", &n, &m, &c);

    int p[51];
    for (int i = 1; i <= c; i++) {
        scanf("%d", &p[i]);
    }

    int grid[n][m];
    int color_index = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid[i][j] = color_index;
            p[color_index]--;
            if (p[color_index] == 0) {
                color_index++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}