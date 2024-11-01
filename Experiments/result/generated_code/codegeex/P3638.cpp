#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10
#define MAXW 501
#define MAXH 501

int n, w, h;
int robot[MAXW][MAXH];
int visited[MAXW][MAXH][4];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
char grid[MAXH][MAXW];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int bfs(int startX, int startY, int dir) {
    int x = startX, y = startY;
    int count = 0;
    while (1) {
        if (grid[y][x] == 'x') {
            break;
        }
        if (grid[y][x] == 'A' && dir != 3) {
            dir = (dir + 1) % 4;
        } else if (grid[y][x] == 'C' && dir != 1) {
            dir = (dir + 3) % 4;
        }
        x += dx[dir];
        y += dy[dir];
        count++;
        if (robot[x][y] && robot[x][y] != -1) {
            return robot[x][y] + count;
        }
    }
    return -1;
}

int dfs(int step) {
    if (step == n) {
        return 0;
    }
    int minSteps = -1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (robot[i][j] == -1) {
                continue;
            }
            for (int k = 0; k < 4; k++) {
                int newX = i + dx[k];
                int newY = j + dy[k];
                if (newX >= 1 && newX <= w && newY >= 1 && newY <= h && grid[newY][newX] != 'x' && visited[newX][newY][k] == 0) {
                    int result = bfs(newX, newY, k);
                    if (result != -1) {
                        visited[newX][newY][k] = 1;
                        int nextStep = dfs(step + 1);
                        visited[newX][newY][k] = 0;
                        if (nextStep != -1) {
                            minSteps = min(minSteps, step + result + nextStep);
                        }
                    }
                }
            }
        }
    }
    return minSteps;
}

int main() {
    scanf("%d%d%d", &n, &w, &h);
    for (int i = 1; i <= h; i++) {
        scanf("%s", grid[i] + 1);
    }
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= h; j++) {
            if (grid[j][i] >= '1' && grid[j][i] <= '9') {
                robot[i][j] = grid[j][i] - '0';
            } else {
                robot[i][j] = -1;
            }
        }
    }
    memset(visited, 0, sizeof(visited));
    int result = dfs(0);
    printf("%d\n", result);
    return 0;
}