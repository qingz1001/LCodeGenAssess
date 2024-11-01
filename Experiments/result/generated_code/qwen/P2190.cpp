#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *board = (int *)calloc(n + 1, sizeof(int));
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        if (x > y) {
            y += n;
        }
        for (int j = x - 1; j < y; ++j) {
            board[j % n] += z;
        }
    }

    int max_board = 0;
    for (int i = 0; i < n; ++i) {
        if (max_board < board[i]) {
            max_board = board[i];
        }
    }

    printf("%d\n", (max_board + 35) / 36);

    free(board);
    return 0;
}