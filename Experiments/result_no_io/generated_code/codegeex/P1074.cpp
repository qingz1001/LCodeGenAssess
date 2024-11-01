#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int score[9][9] = {
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

int board[9][9];
int row[9][10], col[9][10], block[3][3][10];
int unassigned[81]; // 用来存储所有未赋值的格子的坐标
int unassigned_count;

int isSafe(int row, int col, int num) {
    return !row[9 - num] && !col[9 - num] && !block[row / 3][col / 3][9 - num];
}

void updateBoard(int row, int col, int num, int flag) {
    board[row][col] = flag ? num : 0;
    row[9 - num] = flag;
    col[9 - num] = flag;
    block[row / 3][col / 3][9 - num] = flag;
}

int solveSudoku(int index) {
    if (index == unassigned_count) {
        int total_score = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                total_score += score[i][j] * board[i][j];
            }
        }
        return total_score;
    }

    int row = unassigned[index] / 9;
    int col = unassigned[index] % 9;

    int max_score = -1;
    for (int num = 1; num <= 9; num++) {
        if (isSafe(row, col, num)) {
            updateBoard(row, col, num, 1);
            int current_score = solveSudoku(index + 1);
            max_score = MAX(max_score, current_score);
            updateBoard(row, col, num, 0);
        }
    }

    return max_score;
}

int main() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 0) {
                unassigned[unassigned_count++] = i * 9 + j;
            } else {
                updateBoard(i, j, board[i][j], 1);
            }
        }
    }

    int result = solveSudoku(0);
    printf("%d\n", result);

    return 0;
}