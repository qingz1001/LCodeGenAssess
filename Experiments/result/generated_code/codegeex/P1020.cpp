#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, max, min, *heights, *dp, *count;

    // 读取输入
    scanf("%d", &n);
    heights = (int *)malloc(n * sizeof(int));
    dp = (int *)malloc(n * sizeof(int));
    count = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    // 初始化dp和count数组
    dp[0] = 1;
    count[0] = 1;
    max = 1;
    min = n;

    // 计算最多能拦截多少导弹
    for (i = 1; i < n; i++) {
        dp[i] = 1;
        for (j = 0; j < i; j++) {
            if (heights[i] <= heights[j]) {
                dp[i] = (dp[i] < dp[j] + 1) ? dp[j] + 1 : dp[i];
            }
        }
        max = (max < dp[i]) ? dp[i] : max;
    }

    // 计算最少要配备多少套系统
    for (i = 0; i < n; i++) {
        count[i] = 1;
    }
    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (heights[i] <= heights[j]) {
                count[i] = (count[i] > count[j] + 1) ? count[i] : count[j] + 1;
            }
        }
        min = (min > count[i]) ? min : count[i];
    }

    // 输出结果
    printf("%d\n%d\n", max, min);

    // 释放内存
    free(heights);
    free(dp);
    free(count);

    return 0;
}