#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

int board[MAXN][MAXN];
int n, m;

int place(int x, int y) {
    if (x + 1 < n && y + 1 < m && !board[x+1][y] && !board[x][y+1] && !board[x+1][y+1]) {
        board[x+1][y] = 1;
        board[x][y+1] = 1;
        board[x+1][y+1] = 1;
        return 1;
    }
    if (x - 1 >= 0 && y + 1 < m && !board[x-1][y] && !board[x][y+1] && !board[x-1][y+1]) {
        board[x-1][y] = 1;
        board[x][y+1] = 1;
        board[x-1][y+1] = 1;
        return 1;
    }
    if (x + 1 < n && y - 1 >= 0 && !board[x+1][y] && !board[x][y-1] && !board[x+1][y-1]) {
        board[x+1][y] = 1;
        board[x][y-1] = 1;
        board[x+1][y-1] = 1;
        return 1;
    }
    if (x - 1 >= 0 && y - 1 >= 0 && !board[x-1][y] && !board[x][y-1] && !board[x-1][y-1]) {
        board[x-1][y] = 1;
        board[x][y-1] = 1;
        board[x-1][y-1] = 1;
        return 1;
    }
    return 0;
}

void remove(int x, int y) {
    board[x+1][y] = 0;
    board[x][y+1] = 0;
    board[x+1][y+1] = 0;
}

int solve(int x, int y, int count) {
    if (x == n) return count;
    if (y == m) return solve(x + 1, 0, count);
    if (!board[x][y]) {
        if (place(x, y)) {
            count++;
            return solve(x, y + 1, count);
        } else {
            return solve(x, y + 1, count);
        }
    } else {
        return solve(x, y + 1, count);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            board[i][j] = 0;
        }
    }
    printf("%d\n", solve(0, 0, 0));
    return 0;
}