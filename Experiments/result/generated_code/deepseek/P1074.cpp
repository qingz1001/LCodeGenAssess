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

int maxScore = -1;

int isValid(int row, int col, int num) {
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

void solveSudoku(int row, int col, int currentScore) {
    if (row == N) {
        if (currentScore > maxScore) {
            maxScore = currentScore;
        }
        return;
    }

    int nextRow = row;
    int nextCol = col + 1;
    if (nextCol == N) {
        nextRow++;
        nextCol = 0;
    }

    if (grid[row][col] != UNASSIGNED) {
        solveSudoku(nextRow, nextCol, currentScore + grid[row][col] * score[row][col]);
        return;
    }

    for (int num = 1; num <= 9; num++) {
        if (isValid(row, col, num)) {
            grid[row][col] = num;
            solveSudoku(nextRow, nextCol, currentScore + num * score[row][col]);
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

    int initialScore = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] != UNASSIGNED) {
                initialScore += grid[i][j] * score[i][j];
            }
        }
    }

    solveSudoku(0, 0, initialScore);

    printf("%d\n", maxScore);

    return 0;
}