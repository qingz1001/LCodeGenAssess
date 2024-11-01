#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 4

int board[N][N];
bool used[17];
int start_i, start_j;

bool check_sum(int a, int b, int c, int d) {
    return (board[a/4][a%4] + board[b/4][b%4] + board[c/4][c%4] + board[d/4][d%4] == 34);
}

bool is_valid() {
    // Check corners
    if (!check_sum(0, 3, 12, 15)) return false;
    
    // Check 2x2 squares
    if (!check_sum(0, 1, 4, 5)) return false;
    if (!check_sum(2, 3, 6, 7)) return false;
    if (!check_sum(8, 9, 12, 13)) return false;
    if (!check_sum(10, 11, 14, 15)) return false;
    
    // Check center
    if (!check_sum(5, 6, 9, 10)) return false;
    
    // Check rows
    for (int i = 0; i < N; i++) {
        if (!check_sum(i*4, i*4+1, i*4+2, i*4+3)) return false;
    }
    
    // Check columns
    for (int j = 0; j < N; j++) {
        if (!check_sum(j, j+4, j+8, j+12)) return false;
    }
    
    // Check diagonals
    if (!check_sum(0, 5, 10, 15)) return false;
    if (!check_sum(3, 6, 9, 12)) return false;
    
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

void solve(int pos) {
    if (pos == N*N) {
        if (is_valid()) {
            print_board();
        }
        return;
    }
    
    int i = pos / N;
    int j = pos % N;
    
    if (i == start_i && j == start_j) {
        solve(pos + 1);
        return;
    }
    
    for (int num = 2; num <= 16; num++) {
        if (!used[num]) {
            board[i][j] = num;
            used[num] = true;
            solve(pos + 1);
            used[num] = false;
            board[i][j] = 0;
        }
    }
}

int main() {
    scanf("%d %d", &start_i, &start_j);
    start_i--; start_j--;
    
    memset(board, 0, sizeof(board));
    memset(used, false, sizeof(used));
    
    board[start_i][start_j] = 1;
    used[1] = true;
    
    solve(0);
    
    return 0;
}