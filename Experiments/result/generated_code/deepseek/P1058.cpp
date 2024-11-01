#include <stdio.h>
#include <stdlib.h>

#define MAX_M 50
#define MAX_N 50
#define MAX_HEIGHT 100

char canvas[MAX_HEIGHT * 3 + 2][MAX_M * 4 + MAX_N * 2 + 1];

void draw_cube(int x, int y, int height) {
    for (int i = 0; i < height; i++) {
        // Draw top face
        canvas[y - i][x + i] = '+';
        canvas[y - i][x + i + 1] = '-';
        canvas[y - i][x + i + 2] = '-';
        canvas[y - i][x + i + 3] = '-';
        canvas[y - i][x + i + 4] = '+';

        // Draw right face
        for (int j = 1; j <= 3; j++) {
            canvas[y - i + j][x + i + 4] = '|';
        }
        canvas[y - i + 4][x + i + 4] = '+';

        // Draw front face
        for (int j = 1; j <= 3; j++) {
            canvas[y - i + 4][x + i + j] = '-';
        }
        canvas[y - i + 4][x + i] = '+';

        // Draw diagonal lines
        for (int j = 1; j <= 3; j++) {
            canvas[y - i + j][x + i] = '/';
        }
        canvas[y - i + 4][x + i] = '+';

        // Draw vertical lines
        for (int j = 1; j <= 3; j++) {
            canvas[y - i + j][x + i + 4] = '|';
        }
        canvas[y - i + 4][x + i + 4] = '+';
    }
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

    // Initialize canvas with '.'
    for (int i = 0; i < MAX_HEIGHT * 3 + 2; i++) {
        for (int j = 0; j < MAX_M * 4 + MAX_N * 2 + 1; j++) {
            canvas[i][j] = '.';
        }
    }

    // Draw cubes
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int x = j * 4 + (m - i - 1) * 2;
            int y = (m - i - 1) * 3 + grid[i][j] * 3;
            draw_cube(x, y, grid[i][j]);
        }
    }

    // Print canvas
    for (int i = 0; i < MAX_HEIGHT * 3 + 2; i++) {
        for (int j = 0; j < MAX_M * 4 + MAX_N * 2 + 1; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }

    return 0;
}