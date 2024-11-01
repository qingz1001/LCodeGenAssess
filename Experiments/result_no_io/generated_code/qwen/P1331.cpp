#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1005

int R, C;
char board[MAX_SIZE][MAX_SIZE];

void dfs(int x, int y) {
    if (x < 0 || x >= R || y < 0 || y >= C || board[x][y] == '.') return;
    board[x][y] = '.';
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int count_ships() {
    int count = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == '#') {
                count++;
                dfs(i, j);
            }
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            scanf(" %c", &board[i][j]);
        }
    }

    int ship_count = count_ships();

    // Check for adjacent ships
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == '#') {
                if ((i > 0 && board[i - 1][j] == '#') || 
                    (i < R - 1 && board[i + 1][j] == '#') || 
                    (j > 0 && board[i][j - 1] == '#') || 
                    (j < C - 1 && board[i][j + 1] == '#')) {
                    printf("Bad placement.\n");
                    return 0;
                }
            }
        }
    }

    printf("There are %d ships.\n", ship_count);

    return 0;
}