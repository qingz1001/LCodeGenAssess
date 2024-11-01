#include <stdio.h>
#include <stdlib.h>

#define MAXN 105

int board[MAXN][MAXN];
int target[MAXN][MAXN];

void flipRow(int row, int m) {
    for (int j = 0; j < m; j++) {
        board[row][j] = 1 - board[row][j];
    }
}

void swapColumns(int col1, int col2, int n) {
    for (int i = 0; i < n; i++) {
        int temp = board[i][col1];
        board[i][col1] = board[i][col2];
        board[i][col2] = temp;
    }
}

int canTransform(int n, int m) {
    for (int i = 0; i < n; i++) {
        if (board[i][0] != target[i][0]) {
            flipRow(i, m);
        }
    }

    for (int j = 1; j < m; j++) {
        if (board[0][j] != target[0][j]) {
            swapColumns(j, 0, n);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] != target[i][j]) {
                return 0;
            }
        }
    }

    return 1;
}

int main() {
    int k;
    scanf("%d", &k);

    while (k--) {
        int n, m;
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &board[i][j]);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &target[i][j]);
            }
        }

        if (canTransform(n, m)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}