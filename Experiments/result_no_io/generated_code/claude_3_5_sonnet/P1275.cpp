#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 100

int board1[MAX_N][MAX_M], board2[MAX_N][MAX_M];
int n, m;

void sort_columns(int board[MAX_N][MAX_M]) {
    for (int j = 0; j < m; j++) {
        for (int k = j + 1; k < m; k++) {
            if (memcmp(&board[0][j], &board[0][k], n * sizeof(int)) > 0) {
                for (int i = 0; i < n; i++) {
                    int temp = board[i][j];
                    board[i][j] = board[i][k];
                    board[i][k] = temp;
                }
            }
        }
    }
}

int compare_boards() {
    for (int i = 0; i < n; i++) {
        int diff = 0;
        for (int j = 0; j < m; j++) {
            if (board1[i][j] != board2[i][j]) {
                diff++;
            }
        }
        if (diff % 2 != 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int k;
    scanf("%d", &k);

    while (k--) {
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &board1[i][j]);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &board2[i][j]);
            }
        }

        sort_columns(board1);
        sort_columns(board2);

        if (compare_boards()) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}