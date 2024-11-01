#include <stdio.h>
#include <string.h>

#define N 5
#define MAX_K 13

int board[N][N];
int count[MAX_K];
int n, total;

void dfs(int row, int col, int placed) {
    if (placed == n) {
        int k = 0;
        for (int i = 0; i < N; i++) {
            if (board[i][0] + board[i][1] + board[i][2] + board[i][3] + board[i][4] == 5) k++;
            if (board[0][i] + board[1][i] + board[2][i] + board[3][i] + board[4][i] == 5) k++;
        }
        if (board[0][0] + board[1][1] + board[2][2] + board[3][3] + board[4][4] == 5) k++;
        if (board[0][4] + board[1][3] + board[2][2] + board[3][1] + board[4][0] == 5) k++;
        count[k]++;
        return;
    }
    
    if (col == N) {
        row++;
        col = 0;
    }
    
    if (row == N) return;
    
    board[row][col] = 1;
    dfs(row, col + 1, placed + 1);
    board[row][col] = 0;
    dfs(row, col + 1, placed);
}

int main() {
    scanf("%d", &n);
    
    memset(count, 0, sizeof(count));
    dfs(0, 0, 0);
    
    for (int i = 1; i < MAX_K; i++) {
        if (count[i] > 0) {
            total += i;
        }
    }
    
    printf("%d\n", total);
    
    return 0;
}