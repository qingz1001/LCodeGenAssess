#include <stdio.h>
#include <string.h>

#define MAX_HEIGHT 6
#define MAX_WIDTH 6

// 定义方向数组，用于表示上下左右四个方向
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

// 定义底板数组
char board[MAX_HEIGHT][MAX_WIDTH];

// 检查当前位置是否可以放置方块
int canPlaceBlock(int x, int y) {
    if (x < 0 || x >= MAX_HEIGHT || y < 0 || y >= MAX_WIDTH) {
        return 0;
    }
    return board[x][y] == '.';
}

// 放置方块
void placeBlock(int x, int y, char color) {
    board[x][y] = color;
    board[x + 1][y] = color;
    board[x][y + 1] = color;
    board[x + 1][y + 1] = color;
}

// 移除方块
void removeBlock(int x, int y) {
    board[x][y] = '.';
    board[x + 1][y] = '.';
    board[x][y + 1] = '.';
    board[x + 1][y + 1] = '.';
}

// 深度优先搜索
void dfs(int x, int y, int height, long long *count) {
    // 如果已经放置到最后一行，计数加一
    if (x >= MAX_HEIGHT) {
        (*count)++;
        return;
    }

    // 如果当前位置已经超出边界，返回
    if (y >= MAX_WIDTH) {
        dfs(x + 1, 0, height, count);
        return;
    }

    // 如果当前位置不能放置方块，继续下一个位置
    if (!canPlaceBlock(x, y)) {
        dfs(x, y + 1, height, count);
        return;
    }

    // 尝试放置不同颜色的方块
    placeBlock(x, y, 'W');
    dfs(x, y + 1, height, count);
    removeBlock(x, y);

    placeBlock(x, y, 'G');
    dfs(x, y + 1, height, count);
    removeBlock(x, y);

    placeBlock(x, y, 'B');
    dfs(x, y + 1, height, count);
    removeBlock(x, y);
}

int main() {
    int height;
    scanf("%d", &height);

    // 读取输入
    for (int i = 0; i < height; i++) {
        scanf("%s", board[i]);
    }
    for (int i = 0; i < height; i++) {
        scanf("%s", board[i + height]);
    }

    long long count = 0;
    dfs(0, 0, height, &count);

    printf("%lld\n", count);
    return 0;
}