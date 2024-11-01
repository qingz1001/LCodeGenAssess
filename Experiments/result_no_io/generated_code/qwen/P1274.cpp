#include <stdio.h>
#include <stdlib.h>

#define N 4
#define TARGET_SUM 34

int board[N][N];
int used[17];

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int isValid(int row, int col, int num) {
    if (used[num]) return 0;

    // Check row and column sums
    for (int i = 0; i < N; i++) {
        if (board[row][i] + board[col][i] != TARGET_SUM - num) return 0;
    }

    // Check diagonal sums
    if (row == col && board[row][col] + board[N-1-row][N-1-col] != TARGET_SUM - num) return 0;
    if (row + col == N-1 && board[row][col] + board[N-1-row][col] != TARGET_SUM - num) return 0;

    // Check 2x2 squares
    for (int r = 0; r <= N-2; r++) {
        for (int c = 0; c <= N-2; c++) {
            int sum = board[r][c] + board[r][c+1] + board[r+1][c] + board[r+1][c+1];
            if (r == row && c == col) sum += num;
            else if (r == row || c == col) continue;
            if (sum != TARGET_SUM) return 0;
        }
    }

    return 1;
}

void solve(int row, int col, int num) {
    if (num > 16) {
        printBoard();
        printf("\n");
        return;
    }

    if (isValid(row, col, num)) {
        board[row][col] = num;
        used[num] = 1;

        if (col == N-1) {
            solve(row+1, 0, num+1);
        } else {
            solve(row, col+1, num+1);
        }

        used[num] = 0;
    }

    if (col == N-1) {
        solve(row+1, 0, num);
    } else {
        solve(row, col+1, num);
    }
}

int main() {
    int i, j;
    scanf("%d %d", &i, &j);

    i--; j--;
    board[i][j] = 1;
    used[1] = 1;

    solve(0, 0, 2);

    return 0;
}