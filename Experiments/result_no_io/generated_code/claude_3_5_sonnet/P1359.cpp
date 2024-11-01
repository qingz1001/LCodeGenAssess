#include <stdio.h>
#include <limits.h>

#define MAX_N 200

int main() {
    int n;
    int r[MAX_N][MAX_N];
    int dp[MAX_N];
    
    scanf("%d", &n);
    
    // 读取半矩阵
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            scanf("%d", &r[i][j]);
        }
    }
    
    // 初始化dp数组
    for (int i = 0; i < n; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;
    
    // 动态规划
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] != INT_MAX && dp[j] + r[j][i] < dp[i]) {
                dp[i] = dp[j] + r[j][i];
            }
        }
    }
    
    // 输出结果
    printf("%d\n", dp[n-1]);
    
    return 0;
}