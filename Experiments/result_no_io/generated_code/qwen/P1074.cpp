#include <stdio.h>
#include <stdlib.h>

#define N 9
#define MAX_VALUE 1000000

int board[N][N];
int score[N][N] = {
    {10, 10, 10, 9, 9, 9, 8, 8, 8},
    {10, 10, 10, 9, 9, 9, 8, 8, 8},
    {10, 10, 10, 9, 9, 9, 8, 8, 8},
    {9, 9, 9, 8, 8, 8, 7, 7, 7},
    {9, 9, 9, 8, 8, 8, 7, 7, 7},
    {9, 9, 9, 8, 8, 8, 7, 7, 7},
    {8, 8, 8, 7, 7, 7, 6, 6, 6},
    {8, 8, 8, 7, 7, 7, 6, 6, 6},
    {8, 8, 8, 7, 7, 7, 6, 6, 6}
};

int is_valid(int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num || board[i][col] == num) return 0;
    }
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[start_row + i][start_col + j] == num) return 0;
        }
    }
    return 1;
}

int solve(int row, int col) {
    if (row == N) return 0;
    if (col == N) return solve(row + 1, 0);
    if (board[row][col] != 0) return solve(row, col + 1);

    int max_score = -1;
    for (int num = 1; num <= N; num++) {
        if (is_valid(row, col, num)) {
            board[row][col] = num;
            int current_score = score[row][col] * num + solve(row, col + 1);
            if (current_score > max_score) max_score = current_score;
            board[row][col] = 0;
        }
    }

    return max_score;
}

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    int result = solve(0, 0);
    printf("%d\n", result);
    return 0;
}