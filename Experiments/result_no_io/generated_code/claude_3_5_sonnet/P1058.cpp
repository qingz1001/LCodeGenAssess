#include <stdio.h>
#include <string.h>

#define MAX_M 50
#define MAX_N 50
#define MAX_H 100

char map[MAX_M * 3][MAX_N * 4 + MAX_M];

void draw_block(int x, int y) {
    map[x][y] = '+';
    map[x][y+1] = map[x][y+2] = map[x][y+3] = '-';
    map[x][y+4] = '+';
    map[x+1][y] = '|';
    map[x+1][y+1] = map[x+1][y+2] = map[x+1][y+3] = ' ';
    map[x+1][y+4] = '|';
    map[x+2][y] = '+';
    map[x+2][y+1] = map[x+2][y+2] = map[x+2][y+3] = '-';
    map[x+2][y+4] = '+';
    map[x][y-1] = map[x+1][y-1] = '/';
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int blocks[MAX_M][MAX_N];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &blocks[i][j]);
        }
    }

    memset(map, '.', sizeof(map));

    for (int i = m - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            int x = (m - 1 - i) * 2 + blocks[i][j] * 3 - 1;
            int y = (m - 1 - i) + j * 4;
            for (int k = 0; k < blocks[i][j]; k++) {
                draw_block(x - k * 3, y);
            }
        }
    }

    int max_row = m * 2 + MAX_H * 3;
    int max_col = n * 4 + m;

    while (max_row > 0 && strspn(map[max_row - 1], ".") == max_col) {
        max_row--;
    }

    for (int i = 0; i < max_row; i++) {
        for (int j = 0; j < max_col; j++) {
            putchar(map[i][j]);
        }
        putchar('\n');
    }

    return 0;
}