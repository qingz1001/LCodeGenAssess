#include <stdio.h>
#include <stdlib.h>

#define N 9
#define UNASSIGNED 0

int grid[N][N];
int score[N][N] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 9, 10, 9, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6}
};

int max_score = -1;

int is_safe(int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return 0;
        }
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }
    return 1;
}

void calculate_score() {
    int current_score = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            current_score += grid[i][j] * score[i][j];
        }
    }
    if (current_score > max_score) {
        max_score = current_score;
    }
}

void solve_sudoku(int row, int col) {
    if (row == N) {
        calculate_score();
        return;
    }
    if (col == N) {
        solve_sudoku(row + 1, 0);
        return;
    }
    if (grid[row][col] != UNASSIGNED) {
        solve_sudoku(row, col + 1);
        return;
    }
    for (int num = 1; num <= 9; num++) {
        if (is_safe(row, col, num)) {
            grid[row][col] = num;
            solve_sudoku(row, col + 1);
            grid[row][col] = UNASSIGNED;
        }
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    solve_sudoku(0, 0);
    printf("%d\n", max_score);
    return 0;
}