#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 50
#define MAX_N 50
#define MAX_HEIGHT 100

char canvas[MAX_HEIGHT * 3 + 1][MAX_M * 4 + MAX_N * 2 + 1];

void draw_block(int x, int y) {
    canvas[y][x] = canvas[y + 1][x + 1] = canvas[y + 2][x + 2] = '+';
    canvas[y][x + 1] = canvas[y][x + 2] = canvas[y][x + 3] = '-';
    canvas[y + 1][x] = canvas[y + 2][x] = '|';
    canvas[y + 1][x + 2] = canvas[y + 2][x + 2] = '|';
    canvas[y + 2][x + 1] = '/';
    canvas[y + 1][x + 3] = canvas[y + 2][x + 3] = '/';
    canvas[y + 3][x + 1] = canvas[y + 3][x + 2] = canvas[y + 3][x + 3] = '-';
    canvas[y + 3][x] = canvas[y + 3][x + 4] = '+';
    canvas[y + 4][x] = canvas[y + 4][x + 1] = canvas[y + 4][x + 2] = '|';
    canvas[y + 4][x + 3] = '/';
    canvas[y + 5][x] = canvas[y + 5][x + 1] = canvas[y + 5][x + 2] = '|';
    canvas[y + 5][x + 3] = '/';
    canvas[y + 5][x + 4] = '+';
}

int main() {
    int m, n;
    int grid[MAX_M][MAX_N];
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    memset(canvas, '.', sizeof(canvas));

    int max_height = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] > max_height) {
                max_height = grid[i][j];
            }
        }
    }

    int width = m * 4 + n * 2 + 1;
    int height = max_height * 3 + 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < grid[i][j]; k++) {
                draw_block(j * 2 + (m - i - 1) * 4, height - 3 * (k + 1));
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }

    return 0;
}