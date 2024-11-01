#include <stdio.h>

int main() {
    int n, c;
    scanf("%d %d", &n, &c);
    int position[n], power[n];
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &position[i], &power[i]);
    }
    
    int dp[n+1][n+1][2]; // dp数组，用于记录状态
    
    // 初始化dp数组
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j][0] = dp[i][j][1] = INT_MAX;
        }
    }
    
    // 老张所在位置的路灯已经关闭
    dp[c][c][0] = dp[c][c][1] = 0;
    
    // 遍历所有可能的状态
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            // 从左边过来，关闭最右边的灯
            dp[i][j][0] = dp[i][j-1][0] + power[j-1] * (position[j] - position[j-1]);
            // 从右边过来，关闭最左边的灯
            dp[i][j][1] = dp[i+1][j][1] + power[i] * (position[i+1] - position[i]);
        }
    }
    
    // 找到最小的功耗
    int min_power = INT_MAX;
    for (int i = 1; i <= n; i++) {
        min_power = (min_power < dp[1][n][i]) ? min_power : dp[1][n][i];
    }
    
    printf("%d\n", min_power);
    return 0;
}