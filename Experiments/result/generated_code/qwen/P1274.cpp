#include <stdio.h>
#include <stdlib.h>

#define N 4
#define TARGET_SUM 34

int board[N][N];
int row_sum[N], col_sum[N], diag_sum[2];

void print_board() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int check_validity(int r, int c, int num) {
    if (row_sum[r] + num > TARGET_SUM || col_sum[c] + num > TARGET_SUM ||
        (r == c && diag_sum[0] + num > TARGET_SUM) ||
        (r + c == N - 1 && diag_sum[1] + num > TARGET_SUM)) {
        return 0;
    }
    return 1;
}

void backtrack(int r, int c) {
    if (r == N) {
        print_board();
        printf("\n");
        return;
    }

    if (c == N) {
        backtrack(r + 1, 0);
        return;
    }

    if (r == 0 && c == 0) {
        board[r][c] = 1;
        row_sum[r] += 1;
        col_sum[c] += 1;
        diag_sum[0] += 1;
        diag_sum[1] += 1;
        backtrack(r, c + 1);
        board[r][c] = 0;
        row_sum[r] -= 1;
        col_sum[c] -= 1;
        diag_sum[0] -= 1;
        diag_sum[1] -= 1;
    } else {
        for (int num = 2; num <= 16; num++) {
            if (!check_validity(r, c, num)) continue;
            board[r][c] = num;
            row_sum[r] += num;
            col_sum[c] += num;
            if (r == c) diag_sum[0] += num;
            if (r + c == N - 1) diag_sum[1] += num;
            backtrack(r, c + 1);
            board[r][c] = 0;
            row_sum[r] -= num;
            col_sum[c] -= num;
            if (r == c) diag_sum[0] -= num;
            if (r + c == N - 1) diag_sum[1] -= num;
        }
    }
}

int main() {
    int i, j;
    scanf("%d %d", &i, &j);

    i--; j--; // Convert to 0-based index
    board[i][j] = 1;
    row_sum[i] += 1;
    col_sum[j] += 1;
    diag_sum[0] += 1;
    diag_sum[1] += 1;

    backtrack(0, 0);

    return 0;
}