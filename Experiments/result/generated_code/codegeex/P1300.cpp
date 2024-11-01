#include <stdio.h>
#include <string.h>

#define MAXN 31

int h, w;
char map[MAXN][MAXN];
int cost[MAXN][MAXN][4]; // cost[i][j][k] 表示在第 i 行第 j 列，方向为 k 时的最小花费

// 定义四个方向：北、东、南、西
enum Direction { NORTH, EAST, SOUTH, WEST };

// 判断当前位置是否有效
int isValid(int x, int y) {
    return x >= 0 && x < h && y >= 0 && y < w && map[x][y] != '.';
}

// 获取下一个位置
void getNext(int x, int y, enum Direction dir, int *nx, int *ny) {
    switch (dir) {
        case NORTH: *nx = x - 1; *ny = y; break;
        case EAST:  *nx = x; *ny = y + 1; break;
        case SOUTH: *nx = x + 1; *ny = y; break;
        case WEST:  *nx = x; *ny = y - 1; break;
    }
}

int main() {
    scanf("%d%d", &h, &w);
    for (int i = 0; i < h; i++) {
        scanf("%s", map[i]);
    }

    memset(cost, 0x3f, sizeof(cost)); // 初始化为无穷大

    int startX, startY, startDir;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (map[i][j] == 'N') {
                startX = i;
                startY = j;
                startDir = NORTH;
                cost[i][j][NORTH] = 0;
            } else if (map[i][j] == 'E') {
                startX = i;
                startY = j;
                startDir = EAST;
                cost[i][j][EAST] = 0;
            } else if (map[i][j] == 'S') {
                startX = i;
                startY = j;
                startDir = SOUTH;
                cost[i][j][SOUTH] = 0;
            } else if (map[i][j] == 'W') {
                startX = i;
                startY = j;
                startDir = WEST;
                cost[i][j][WEST] = 0;
            }
        }
    }

    // 定义四个方向的移动
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    // 定义费用
    int fees[4] = {1, 5, 10, 10};

    // 四个方向分别进行广度优先搜索
    for (int d = 0; d < 4; d++) {
        int x = startX, y = startY;
        while (isValid(x, y)) {
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (isValid(nx, ny) && cost[nx][ny][i] > cost[x][y][d] + fees[(d + i) % 4]) {
                    cost[nx][ny][i] = cost[x][y][d] + fees[(d + i) % 4];
                }
            }
            x += dx[d];
            y += dy[d];
        }
    }

    int endX, endY;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (map[i][j] == 'F') {
                endX = i;
                endY = j;
            }
        }
    }

    int minCost = cost[endX][endY][0];
    for (int i = 1; i < 4; i++) {
        if (cost[endX][endY][i] < minCost) {
            minCost = cost[endX][endY][i];
        }
    }

    printf("%d\n", minCost);
    return 0;
}