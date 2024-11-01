#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1005

int board[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int R, C;

void dfs(int x, int y) {
    if (x < 0 || x >= R || y < 0 || y >= C || board[x][y] == 0 || visited[x][y]) return;
    visited[x][y] = 1;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int count_ships() {
    int count = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == 1 && !visited[i][j]) {
                dfs(i, j);
                count++;
            }
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            char ch;
            scanf(" %c", &ch);
            board[i][j] = (ch == '#') ? 1 : 0;
        }
    }

    memset(visited, 0, sizeof(visited));
    int ship_count = count_ships();

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (board[i][j] == 1 && !visited[i][j]) {
                printf("Bad placement.\n");
                return 0;
            }
        }
    }

    printf("There are %d ships.\n", ship_count);
    return 0;
}