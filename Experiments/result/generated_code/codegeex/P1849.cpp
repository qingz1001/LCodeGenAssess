#include <stdio.h>
#include <string.h>

int n, sx, sy, map[1005][1005], dp[1005][1005];

int main() {
    // 读取输入
    scanf("%d%d%d", &n, &sx, &sy);
    memset(map, 0, sizeof(map));
    memset(dp, 0x3f, sizeof(dp));

    // 标记干草堆的位置
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        map[x][y] = 1;
    }

    // 初始化起点的dp值
    dp[sx][sy] = 0;

    // 动态规划求解
    for (int x = 1; x <= 1000; x++) {
        for (int y = 1; y <= 1000; y++) {
            if (x > 1) dp[x][y] = (dp[x][y] < dp[x-1][y] + map[x][y]) ? dp[x][y] : dp[x-1][y] + map[x][y];
            if (y > 1) dp[x][y] = (dp[x][y] < dp[x][y-1] + map[x][y]) ? dp[x][y] : dp[x][y-1] + map[x][y];
            if (x < 1000) dp[x][y] = (dp[x][y] < dp[x+1][y] + map[x][y]) ? dp[x][y] : dp[x+1][y] + map[x][y];
            if (y < 1000) dp[x][y] = (dp[x][y] < dp[x][y+1] + map[x][y]) ? dp[x][y] : dp[x][y+1] + map[x][y];
        }
    }

    // 输出结果
    printf("%d\n", dp[0][0]);
    return 0;
}