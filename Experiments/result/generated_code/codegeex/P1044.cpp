#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    // 定义一个数组来存储可能的输出序列的总数
    long long dp[20] = {0};
    
    // 初始化基本情况
    dp[0] = 1; // 空序列
    
    // 动态规划计算可能的输出序列的总数
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 0; j--) {
            dp[j] = dp[j] + dp[j-1];
        }
    }
    
    // 输出结果，即 dp[n]
    printf("%lld\n", dp[n]);
    
    return 0;
}