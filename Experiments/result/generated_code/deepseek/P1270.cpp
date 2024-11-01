#include <stdio.h>
#include <stdlib.h>

#define MAX_TIME 6000
#define MAX_PAINTS 20
#define MAX_ROOMS 100

int max(int a, int b) {
    return a > b ? a : b;
}

int dfs(int time_left, int *corridors, int index, int *dp) {
    if (time_left <= 1) return 0; // 如果时间不够逃跑，直接返回0
    if (dp[time_left] != -1) return dp[time_left]; // 如果已经计算过，直接返回结果

    int corridor_time = corridors[index];
    int paintings = corridors[index + 1];

    if (paintings == 0) {
        // 分叉走廊
        int left_child = dfs(time_left - corridor_time, corridors, index + 2, dp);
        int right_child = dfs(time_left - corridor_time, corridors, index + 2 + 2 * left_child, dp);
        dp[time_left] = max(left_child, right_child);
    } else {
        // 展览室
        int max_paintings = (time_left - 1) / 5; // 计算最多能偷多少幅画
        max_paintings = max(0, max_paintings); // 至少偷0幅画
        max_paintings = min(max_paintings, paintings); // 不能超过展室里的画数
        dp[time_left] = max_paintings;
    }

    return dp[time_left];
}

int main() {
    int police_time;
    scanf("%d", &police_time);

    int corridors[MAX_ROOMS * 2];
    int index = 0;
    while (scanf("%d %d", &corridors[index], &corridors[index + 1]) != EOF) {
        index += 2;
    }

    int dp[MAX_TIME + 1];
    for (int i = 0; i <= MAX_TIME; i++) {
        dp[i] = -1;
    }

    int result = dfs(police_time, corridors, 0, dp);
    printf("%d\n", result);

    return 0;
}