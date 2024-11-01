#include <stdio.h>
#include <string.h>

#define MAXN 105

char grid[MAXN][MAXN];
int visited[MAXN][MAXN];
const int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
const char *word = "yizhong";
int wordLen = strlen(word);

void dfs(int x, int y, int dir) {
    if (grid[x][y] != word[dir]) return;
    if (dir == wordLen - 1) {
        for (int i = 0; i <= wordLen; i++) {
            int nx = x + directions[dir][0] * i;
            int ny = y + directions[dir][1] * i;
            grid[nx][ny] = '*';
        }
        return;
    }
    visited[x][y] = 1;
    for (int d = 0; d < 8; d++) {
        int nx = x + directions[d][0];
        int ny = y + directions[d][1];
        if (nx >= 0 && nx < wordLen && ny >= 0 && ny < wordLen && !visited[nx][ny]) {
            dfs(nx, ny, dir + 1);
        }
    }
    visited[x][y] = 0;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'y' || grid[i][j] == 'z') {
                memset(visited, 0, sizeof(visited));
                dfs(i, j, 0);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%s\n", grid[i]);
    }

    return 0;
}