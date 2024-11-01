#include <stdio.h>
#include <stdlib.h>

#define MAX_R 1000

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int r;
    int triangle[MAX_R][MAX_R];
    int dp[MAX_R][MAX_R];

    scanf("%d", &r);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }

    // 初始化dp数组
    for (int i = 0; i < r; i++) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = 0;
        }
    }

    // 从底部向上计算最大路径和
    for (int i = r - 1; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            if (i == r - 1) {
                dp[i][j] = triangle[i][j];
            } else {
                dp[i][j] = triangle[i][j] + max(dp[i + 1][j], dp[i + 1][j + 1]);
            }
        }
    }

    // 输出最大路径和
    printf("%d\n", dp[0][0]);

    return 0;
}