#include <stdio.h>
#include <stdlib.h>

#define MAXN 20

int n, k, h;
int colors[MAXN];
int board[MAXN][MAXN];
int count = 0;

int is_valid(int x, int y) {
    for (int i = 0; i < n; i++) {
        if (board[x][i] || board[i][y]) {
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
            if (is_valid(i, j)) {
                board[i][j] = 1;
                colors[color_index]--;
                if (colors[color_index] == 0) {
                    backtrack(placed + 1, color_index + 1);
                } else {
                    backtrack(placed + 1, color_index);
                }
                board[i][j] = 0;
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