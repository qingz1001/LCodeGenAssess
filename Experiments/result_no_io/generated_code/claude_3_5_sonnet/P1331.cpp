#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 1000

char board[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];
int R, C;

void dfs(int r, int c) {
    if (r < 0 || r >= R || c < 0 || c >= C || board[r][c] == '.' || visited[r][c]) {
        return;
    }
    
    visited[r][c] = true;
    
    dfs(r-1, c);
    dfs(r+1, c);
    dfs(r, c-1);
    dfs(r, c+1);
}

bool isValidPlacement() {
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (board[r][c] == '#') {
                if ((r > 0 && board[r-1][c] == '#' && !visited[r-1][c]) ||
                    (c > 0 && board[r][c-1] == '#' && !visited[r][c-1])) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d %d", &R, &C);
    
    for (int r = 0; r < R; r++) {
        scanf("%s", board[r]);
    }
    
    int shipCount = 0;
    
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (board[r][c] == '#' && !visited[r][c]) {
                dfs(r, c);
                shipCount++;
            }
        }
    }
    
    if (isValidPlacement()) {
        printf("There are %d ships.\n", shipCount);
    } else {
        printf("Bad placement.\n");
    }
    
    return 0;
}