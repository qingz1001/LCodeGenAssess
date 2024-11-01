#include <stdio.h>
#include <stdlib.h>

#define MAX_R 1000

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int r;
    scanf("%d", &r);

    int triangle[MAX_R][MAX_R] = {0};
    int dp[MAX_R][MAX_R] = {0};

    // 读入数字金字塔
    for (int i = 0; i < r; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &triangle[i][j]);
        }
    }

    // 初始化最后一行的dp值
    for (int j = 0; j < r; j++) {
        dp[r-1][j] = triangle[r-1][j];
    }

    // 自底向上计算dp值
    for (int i = r - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[i][j] = max(dp[i+1][j], dp[i+1][j+1]) + triangle[i][j];
        }
    }

    // 输出最大和
    printf("%d\n", dp[0][0]);

    return 0;
}