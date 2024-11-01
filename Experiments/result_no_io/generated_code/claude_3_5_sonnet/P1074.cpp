#include <stdio.h>
#include <stdbool.h>

#define N 9

int board[N][N];
int score[N][N] = {
    {6,6,6,6,6,6,6,6,6},
    {6,7,7,7,7,7,7,7,6},
    {6,7,8,8,8,8,8,7,6},
    {6,7,8,9,9,9,8,7,6},
    {6,7,8,9,10,9,8,7,6},
    {6,7,8,9,9,9,8,7,6},
    {6,7,8,8,8,8,8,7,6},
    {6,7,7,7,7,7,7,7,6},
    {6,6,6,6,6,6,6,6,6}
};

bool is_valid(int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num) return false;
        if (board[i][col] == num) return false;
    }
    
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + start_row][j + start_col] == num) return false;
        }
    }
    
    return true;
}

int calculate_score() {
    int total = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            total += board[i][j] * score[i][j];
        }
    }
    return total;
}

bool solve(int row, int col) {
    if (row == N - 1 && col == N) return true;
    
    if (col == N) {
        row++;
        col = 0;
    }
    
    if (board[row][col] > 0) return solve(row, col + 1);
    
    for (int num = 9; num >= 1; num--) {
        if (is_valid(row, col, num)) {
            board[row][col] = num;
            if (solve(row, col + 1)) return true;
        }
        board[row][col] = 0;
    }
    
    return false;
}

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &board[i][j]);
        }
    }
    
    if (solve(0, 0)) {
        printf("%d\n", calculate_score());
    } else {
        printf("-1\n");
    }
    
    return 0;
}