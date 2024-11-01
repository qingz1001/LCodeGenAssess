#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);
    int v[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    // 初始化dp数组，dp[i][j]表示第i个位置被第j个人选择时的最优得分
    int dp[n][2];
    memset(dp, 0, sizeof(dp));

    // 计算dp数组
    for (int i = 0; i < n; i++) {
        dp[i][0] = v[i]; // Byteasar选择第i个位置
        dp[i][1] = v[i]; // Operator选择第i个位置

        // 更新dp数组，考虑前一个位置的情况
        if (i > 0) {
            dp[i][0] = (dp[i][0] + dp[i-1][1]); // Byteasar选择第i个位置，Operator选择第i-1个位置
            dp[i][1] = (dp[i][1] + dp[i-1][0]); // Operator选择第i个位置，Byteasar选择第i-1个位置
        }
    }

    // 找到最大得分
    int max_score = 0;
    for (int i = 0; i < n; i++) {
        max_score = (dp[i][0] > max_score) ? dp[i][0] : max_score;
        max_score = (dp[i][1] > max_score) ? dp[i][1] : max_score;
    }

    printf("%d\n", max_score);
    return 0;
}