#include <stdio.h>
#include <stdlib.h>

#define MAXN 51
#define MAXM 51

int n, m;
int castle[MAXN][MAXM];
int visited[MAXN][MAXM];
int area[MAXN * MAXM];
int maxArea = 0;
int roomCount = 0;
int directions[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}}; // W, N, E, S
char directionSymbols[4] = {'W', 'N', 'E', 'S'};

void dfs(int x, int y, int room) {
    visited[x][y] = 1;
    area[room]++;
    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !visited[nx][ny] && !(castle[x][y] & (1 << i))) {
            dfs(nx, ny, room);
        }
    }
}

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &castle[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!visited[i][j]) {
                roomCount++;
                dfs(i, j, roomCount);
                if (area[roomCount] > maxArea) {
                    maxArea = area[roomCount];
                }
            }
        }
    }

    printf("%d\n%d\n", roomCount, maxArea);

    int maxNewArea = 0;
    int bestX = 0, bestY = 0, bestDir = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < 4; k++) {
                int nx = i + directions[k][0];
                int ny = j + directions[k][1];
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && !(castle[i][j] & (1 << k))) {
                    int newArea = area[visited[i][j]] + area[visited[nx][ny]];
                    if (newArea > maxNewArea || (newArea == maxNewArea && i > bestX) || (newArea == maxNewArea && i == bestX && j < bestY)) {
                        maxNewArea = newArea;
                        bestX = i;
                        bestY = j;
                        bestDir = k;
                    }
                }
            }
        }
    }

    printf("%d\n%d %d %c\n", maxNewArea, bestX, bestY, directionSymbols[bestDir]);

    return 0;
}