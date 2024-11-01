#include <stdio.h>
#include <string.h>

#define MAX_N 9
#define MAX_M 9

int n, m;
int board[MAX_N][MAX_M];
int max_count = 0;

// 检查是否可以在(x, y)位置放置T型骨牌
int can_place(int x, int y, int type) {
    switch(type) {
        case 0: // ###
                // .#.
                // .#.
            return x+2 < n && y+2 < m && 
                   !board[x][y] && !board[x][y+1] && !board[x][y+2] && 
                   !board[x+1][y+1] && !board[x+2][y+1];
        case 1: // ..#
                // ###
                // ..#
            return x+2 < n && y+2 < m && 
                   !board[x][y+2] && !board[x+1][y] && !board[x+1][y+1] && 
                   !board[x+1][y+2] && !board[x+2][y+2];
        case 2: // .#.
                // .#.
                // ###
            return x+2 < n && y+2 < m && 
                   !board[x][y+1] && !board[x+1][y+1] && 
                   !board[x+2][y] && !board[x+2][y+1] && !board[x+2][y+2];
        case 3: // #..
                // ###
                // #..
            return x+2 < n && y+2 < m && 
                   !board[x][y] && !board[x+1][y] && !board[x+1][y+1] && 
                   !board[x+1][y+2] && !board[x+2][y];
    }
    return 0;
}

// 在(x, y)位置放置或移除T型骨牌
void place_or_remove(int x, int y, int type, int value) {
    switch(type) {
        case 0:
            board[x][y] = board[x][y+1] = board[x][y+2] = 
            board[x+1][y+1] = board[x+2][y+1] = value;
            break;
        case 1:
            board[x][y+2] = board[x+1][y] = board[x+1][y+1] = 
            board[x+1][y+2] = board[x+2][y+2] = value;
            break;
        case 2:
            board[x][y+1] = board[x+1][y+1] = 
            board[x+2][y] = board[x+2][y+1] = board[x+2][y+2] = value;
            break;
        case 3:
            board[x][y] = board[x+1][y] = board[x+1][y+1] = 
            board[x+1][y+2] = board[x+2][y] = value;
            break;
    }
}

void dfs(int x, int y, int count) {
    if (y == m) {
        y = 0;
        x++;
    }
    if (x == n) {
        if (count > max_count) {
            max_count = count;
        }
        return;
    }

    dfs(x, y + 1, count);

    for (int type = 0; type < 4; type++) {
        if (can_place(x, y, type)) {
            place_or_remove(x, y, type, 1);
            dfs(x, y + 1, count + 1);
            place_or_remove(x, y, type, 0);
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