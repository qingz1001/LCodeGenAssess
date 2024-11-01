#include <stdio.h>
#include <stdlib.h>

#define MAXN 20

int n, k, h;
int colors[MAXN];
int grid[MAXN][MAXN];
int count = 0;

int is_valid(int x, int y) {
    for (int i = 0; i < n; i++) {
        if (grid[x][i] != 0 || grid[i][y] != 0) {
            return 0;
        }
    }
    return 1;
}

void backtrack(int placed, int color_index) {
    if (placed == k) {
        count++;
        return;
    }
    if (color_index >= h) {
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0 && is_valid(i, j)) {
                grid[i][j] = color_index + 1;
                colors[color_index]--;
                if (colors[color_index] == 0) {
                    backtrack(placed + 1, color_index + 1);
                } else {
                    backtrack(placed + 1, color_index);
                }
                grid[i][j] = 0;
                colors[color_index]++;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &k, &h);
    for (int i = 0; i < h; i++) {
        scanf("%d", &colors[i]);
    }

    backtrack(0, 0);
    printf("%d\n", count);

    return 0;
}