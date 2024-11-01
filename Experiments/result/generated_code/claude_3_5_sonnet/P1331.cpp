#include <stdio.h>
#include <string.h>

#define MAX_R 1000
#define MAX_C 1000

char board[MAX_R][MAX_C];
int R, C;
int visited[MAX_R][MAX_C];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y) {
    visited[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < R && ny >= 0 && ny < C && !visited[nx][ny] && board[nx][ny] == '#') {
            dfs(nx, ny);
        }
    }
}

int is_valid() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == '#') {
                if ((i > 0 && board[i-1][j] == '#' && j > 0 && board[i][j-1] == '#') ||
                    (i > 0 && board[i-1][j] == '#' && j < C-1 && board[i][j+1] == '#') ||
                    (i < R-1 && board[i+1][j] == '#' && j > 0 && board[i][j-1] == '#') ||
                    (i < R-1 && board[i+1][j] == '#' && j < C-1 && board[i][j+1] == '#')) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int main() {
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        scanf("%s", board[i]);
    }

    if (!is_valid()) {
        printf("Bad placement.\n");
        return 0;
    }

    int ships = 0;
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == '#' && !visited[i][j]) {
                dfs(i, j);
                ships++;
            }
        }
    }

    printf("There are %d ships.\n", ships);
    return 0;
}