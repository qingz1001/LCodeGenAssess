#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 4

int row_sum[N], col_sum[N], diag_sum[2];
int known[N][N];
int board[N][N];

bool solve(int r, int c) {
    if (r == N) {
        return true;
    }
    
    if (c == N) {
        return solve(r + 1, 0);
    }
    
    if (known[r][c] != 0) {
        board[r][c] = known[r][c];
        return solve(r, c + 1);
    }
    
    for (int val = 1; val <= 300; val++) {
        board[r][c] = val;
        
        int row_total = 0, col_total = 0;
        for (int i = 0; i < N; i++) {
            row_total += board[r][i];
            col_total += board[i][c];
        }
        
        if (row_total > row_sum[r] || col_total > col_sum[c]) {
            continue;
        }
        
        if (r == c && row_total > diag_sum[0]) {
            continue;
        }
        
        if (r + c == N - 1 && row_total > diag_sum[1]) {
            continue;
        }
        
        if (solve(r, c + 1)) {
            return true;
        }
    }
    
    board[r][c] = 0;
    return false;
}

int main() {
    for (int i = 0; i < N; i++) {
        scanf("%d", &row_sum[i]);
    }
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &col_sum[i]);
    }
    
    scanf("%d %d", &diag_sum[0], &diag_sum[1]);
    
    for (int i = 0; i < N; i++) {
        int r, c, val;
        scanf("%d %d %d", &r, &c, &val);
        known[r][c] = val;
    }
    
    solve(0, 0);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}