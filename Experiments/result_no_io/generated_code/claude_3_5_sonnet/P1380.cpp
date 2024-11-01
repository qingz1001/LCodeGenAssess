#include <stdio.h>
#include <string.h>

#define MAX_N 9
#define MAX_M 9

int n, m;
int board[MAX_N][MAX_M];
int max_count = 0;

int can_place(int x, int y, int type) {
    if (type == 0) {
        if (x + 2 >= n || y + 2 >= m) return 0;
        return !board[x][y] && !board[x][y+1] && !board[x][y+2] && 
               !board[x+1][y+1] && !board[x+2][y+1];
    } else if (type == 1) {
        if (x + 2 >= n || y + 2 >= m) return 0;
        return !board[x][y+1] && !board[x+1][y] && !board[x+1][y+1] && 
               !board[x+1][y+2] && !board[x+2][y+1];
    } else if (type == 2) {
        if (x + 2 >= n || y + 2 >= m) return 0;
        return !board[x][y+1] && !board[x+1][y] && !board[x+1][y+1] && 
               !board[x+1][y+2] && !board[x+2][y+1];
    } else {
        if (x + 2 >= n || y + 2 >= m) return 0;
        return !board[x][y] && !board[x+1][y] && !board[x+1][y+1] && 
               !board[x+1][y+2] && !board[x+2][y];
    }
}

void place(int x, int y, int type) {
    if (type == 0) {
        board[x][y] = board[x][y+1] = board[x][y+2] = 
        board[x+1][y+1] = board[x+2][y+1] = 1;
    } else if (type == 1) {
        board[x][y+1] = board[x+1][y] = board[x+1][y+1] = 
        board[x+1][y+2] = board[x+2][y+1] = 1;
    } else if (type == 2) {
        board[x][y+1] = board[x+1][y] = board[x+1][y+1] = 
        board[x+1][y+2] = board[x+2][y+1] = 1;
    } else {
        board[x][y] = board[x+1][y] = board[x+1][y+1] = 
        board[x+1][y+2] = board[x+2][y] = 1;
    }
}

void remove(int x, int y, int type) {
    if (type == 0) {
        board[x][y] = board[x][y+1] = board[x][y+2] = 
        board[x+1][y+1] = board[x+2][y+1] = 0;
    } else if (type == 1) {
        board[x][y+1] = board[x+1][y] = board[x+1][y+1] = 
        board[x+1][y+2] = board[x+2][y+1] = 0;
    } else if (type == 2) {
        board[x][y+1] = board[x+1][y] = board[x+1][y+1] = 
        board[x+1][y+2] = board[x+2][y+1] = 0;
    } else {
        board[x][y] = board[x+1][y] = board[x+1][y+1] = 
        board[x+1][y+2] = board[x+2][y] = 0;
    }
}

void dfs(int x, int y, int count) {
    if (y == m) {
        x++;
        y = 0;
    }
    if (x == n) {
        if (count > max_count) max_count = count;
        return;
    }
    
    dfs(x, y + 1, count);
    
    for (int type = 0; type < 4; type++) {
        if (can_place(x, y, type)) {
            place(x, y, type);
            dfs(x, y + 1, count + 1);
            remove(x, y, type);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    memset(board, 0, sizeof(board));
    dfs(0, 0, 0);
    printf("%d\n", max_count);
    return 0;
}