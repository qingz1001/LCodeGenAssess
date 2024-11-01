#include <stdio.h>
#include <stdbool.h>

#define MAXN 888

char grid[MAXN * 2][MAXN * 2];
int n;

bool is_empty(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    return grid[x1][y1] == ' ' && grid[x2][y2] == ' ' && grid[x3][y3] == ' ' && grid[x4][y4] == ' ';
}

int count_parallelograms() {
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * i + 1; j++) {
            if (grid[i][j] == ' ') {
                for (int k = i + 1; k < n; k++) {
                    for (int l = 0; l < 2 * k + 1; l++) {
                        if (grid[k][l] == ' ') {
                            int dx = k - i;
                            int dy = l - j;
                            if (is_empty(i, j, k, l, i + dy, j + dx, k + dy, l + dx)) {
                                count++;
                            }
                            if (is_empty(i, j, k, l, i - dy, j - dx, k - dy, l - dx)) {
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }

    return count;
}

int main() {
    scanf("%d", &n);
    getchar(); // consume newline

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * i + 1; j++) {
            grid[i][j] = getchar();
        }
        getchar(); // consume newline
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * (n - i - 1) + 1; j++) {
            grid[n + i][j] = getchar();
        }
        getchar(); // consume newline
    }

    printf("%d\n", count_parallelograms());

    return 0;
}