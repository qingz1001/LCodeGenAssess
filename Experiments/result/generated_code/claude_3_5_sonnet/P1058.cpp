#include <stdio.h>
#include <string.h>

#define MAX_M 50
#define MAX_N 50
#define MAX_HEIGHT 100

char canvas[MAX_M * 3 + 1][MAX_N * 4 + 1];
int height[MAX_M][MAX_N];

void init_canvas(int m, int n) {
    for (int i = 0; i < m * 3 + 1; i++) {
        for (int j = 0; j < n * 4 + 1; j++) {
            canvas[i][j] = '.';
        }
        canvas[i][n * 4] = '\0';
    }
}

void draw_top(int x, int y) {
    canvas[x][y] = '+';
    canvas[x][y+1] = canvas[x][y+2] = canvas[x][y+3] = '-';
    canvas[x][y+4] = '+';
}

void draw_left(int x, int y) {
    canvas[x][y] = '|';
    canvas[x+1][y] = '|';
    canvas[x+2][y] = '+';
}

void draw_right(int x, int y) {
    canvas[x][y] = '/';
    canvas[x+1][y] = '|';
    canvas[x+2][y] = '+';
}

void draw_cube(int x, int y) {
    draw_top(x, y);
    draw_left(x, y);
    draw_right(x, y+4);
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &height[i][j]);
        }
    }

    init_canvas(m, n);

    for (int i = m - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            for (int h = 0; h < height[i][j]; h++) {
                int x = (m - 1 - i) * 2 + (n - 1 - j) + h * 2;
                int y = j * 4 + (m - 1 - i);
                draw_cube(x, y);
            }
        }
    }

    for (int i = 0; i < m * 3; i++) {
        printf("%s\n", canvas[i]);
    }

    return 0;
}