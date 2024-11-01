#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 5
#define MAX_CHESS 25

int board[BOARD_SIZE][BOARD_SIZE];
int n, sum_k;
int visited[13];  // 用于记录已出现的k值

void check_lines() {
    int count, k = 0;
    
    // 检查行
    for (int i = 0; i < BOARD_SIZE; i++) {
        count = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j]) count++;
        }
        if (count == 5) k++;
    }
    
    // 检查列
    for (int j = 0; j < BOARD_SIZE; j++) {
        count = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[i][j]) count++;
        }
        if (count == 5) k++;
    }
    
    // 检查主对角线
    count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][i]) count++;
    }
    if (count == 5) k++;
    
    // 检查副对角线
    count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][BOARD_SIZE-1-i]) count++;
    }
    if (count == 5) k++;
    
    if (k > 0 && !visited[k]) {
        sum_k += k;
        visited[k] = 1;
    }
}

void dfs(int placed, int x, int y) {
    if (placed == n) {
        check_lines();
        return;
    }
    
    for (int i = x; i < BOARD_SIZE; i++) {
        for (int j = (i == x ? y : 0); j < BOARD_SIZE; j++) {
            if (!board[i][j]) {
                board[i][j] = 1;
                dfs(placed + 1, i, j + 1);
                board[i][j] = 0;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    memset(visited, 0, sizeof(visited));
    sum_k = 0;
    dfs(0, 0, 0);
    printf("%d\n", sum_k);
    return 0;
}