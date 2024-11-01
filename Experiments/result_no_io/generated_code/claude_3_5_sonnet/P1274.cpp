#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 4

int board[N][N];
bool used[17];
int row, col;

bool check() {
    int sum;
    
    // 检查四个角落
    if (board[0][0] + board[0][3] + board[3][0] + board[3][3] != 34) return false;
    
    // 检查四个2x2方格
    if (board[0][0] + board[0][1] + board[1][0] + board[1][1] != 34) return false;
    if (board[0][2] + board[0][3] + board[1][2] + board[1][3] != 34) return false;
    if (board[2][0] + board[2][1] + board[3][0] + board[3][1] != 34) return false;
    if (board[2][2] + board[2][3] + board[3][2] + board[3][3] != 34) return false;
    
    // 检查中间2x2方格
    if (board[1][1] + board[1][2] + board[2][1] + board[2][2] != 34) return false;
    
    // 检查每行
    for (int i = 0; i < N; i++) {
        sum = 0;
        for (int j = 0; j < N; j++) sum += board[i][j];
        if (sum != 34) return false;
    }
    
    // 检查每列
    for (int j = 0; j < N; j++) {
        sum = 0;
        for (int i = 0; i < N; i++) sum += board[i][j];
        if (sum != 34) return false;
    }
    
    // 检查对角线
    if (board[0][0] + board[1][1] + board[2][2] + board[3][3] != 34) return false;
    if (board[0][3] + board[1][2] + board[2][1] + board[3][0] != 34) return false;
    
    return true;
}

void print_board() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void solve(int r, int c) {
    if (r == N) {
        if (check()) {
            print_board();
        }
        return;
    }
    
    int next_r = (c == N-1) ? r+1 : r;
    int next_c = (c == N-1) ? 0 : c+1;
    
    if (r == row-1 && c == col-1) {
        board[r][c] = 1;
        solve(next_r, next_c);
    } else {
        for (int num = 2; num <= 16; num++) {
            if (!used[num]) {
                board[r][c] = num;
                used[num] = true;
                solve(next_r, next_c);
                used[num] = false;
            }
        }
    }
}

int main() {
    scanf("%d %d", &row, &col);
    
    memset(used, false, sizeof(used));
    used[1] = true;
    
    solve(0, 0);
    
    return 0;
}