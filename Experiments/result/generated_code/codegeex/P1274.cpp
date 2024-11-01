#include <stdio.h>

int board[4][4];
int used[17];

void print_board() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int check_sum(int i, int j, int k, int l) {
    return board[i][j] + board[i][k] + board[l][j] + board[l][k] == 34;
}

int check() {
    // Check corners
    if (!check_sum(0, 0, 0, 3)) return 0;
    if (!check_sum(0, 0, 3, 0)) return 0;
    if (!check_sum(3, 0, 3, 3)) return 0;
    if (!check_sum(3, 3, 0, 3)) return 0;

    // Check 2x2 squares
    if (!check_sum(0, 0, 1, 1)) return 0;
    if (!check_sum(2, 2, 3, 3)) return 0;

    // Check middle 2x2 square
    if (!check_sum(1, 1, 2, 2)) return 0;

    // Check horizontal lines
    for (int i = 0; i < 4; i++) {
        if (!check_sum(i, 0, i, 1)) return 0;
        if (!check_sum(i, 1, i, 2)) return 0;
        if (!check_sum(i, 2, i, 3)) return 0;
    }

    // Check vertical lines
    for (int j = 0; j < 4; j++) {
        if (!check_sum(0, j, 1, j)) return 0;
        if (!check_sum(1, j, 2, j)) return 0;
        if (!check_sum(2, j, 3, j)) return 0;
    }

    // Check diagonals
    if (!check_sum(0, 0, 3, 3)) return 0;
    if (!check_sum(0, 3, 3, 0)) return 0;

    return 1;
}

void solve(int row, int col) {
    if (row == 4) {
        if (check()) {
            print_board();
            printf("\n");
        }
        return;
    }

    for (int num = 2; num <= 16; num++) {
        if (!used[num]) {
            board[row][col] = num;
            used[num] = 1;
            if (col == 3) solve(row + 1, 0);
            else solve(row, col + 1);
            used[num] = 0;
        }
    }
}

int main() {
    int i, j;
    scanf("%d %d", &i, &j);
    board[i - 1][j - 1] = 1;
    used[1] = 1;
    solve(0, 0);
    return 0;
}