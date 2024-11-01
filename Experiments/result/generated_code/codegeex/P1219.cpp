#include <stdio.h>
#include <stdbool.h>

int n;
int count = 0;
int queens[14];

// 检查当前位置是否可以放置皇后
bool is_safe(int row, int col) {
    for (int i = 1; i < row; i++) {
        if (queens[i] == col || 
            queens[i] - i == col - row || 
            queens[i] + i == col + row) {
            return false;
        }
    }
    return true;
}

// 打印当前棋盘的布局
void print_board() {
    for (int i = 1; i <= n; i++) {
        printf("%d ", queens[i]);
    }
    printf("\n");
}

// 深度优先搜索放置皇后
void solve_queens(int row) {
    if (row > n) {
        count++;
        if (count <= 3) {
            print_board();
        }
        return;
    }
    for (int col = 1; col <= n; col++) {
        if (is_safe(row, col)) {
            queens[row] = col;
            solve_queens(row + 1);
        }
    }
}

int main() {
    scanf("%d", &n);
    solve_queens(1);
    printf("%d\n", count);
    return 0;
}