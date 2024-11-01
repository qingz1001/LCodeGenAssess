#include <stdio.h>
#include <string.h>

#define MAX_N 501

int n;
int arr[MAX_N];

int dp[MAX_N][MAX_N];

int main() {
    // 读取输入
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }

    // 初始化dp数组
    memset(dp, 0, sizeof(dp));

    // 动态规划求解最少射出的珠子个数
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            // 如果两端珠子颜色相同且长度大于等于3，则可以消去
            if (arr[i] == arr[j] && len >= 3) {
                dp[i][j] = dp[i + 1][j - 1];
            } else {
                // 尝试在i和j之间插入珠子
                for (int k = i; k < j; k++) {
                    dp[i][j] = dp[i][j] < dp[i][k] + dp[k + 1][j] ? dp[i][k] + dp[k + 1][j] : dp[i][j];
                }
                // 尝试在i和j之间插入与两端珠子颜色相同的珠子
                for (int k = i - 1, c = arr[i]; k >= 1 && arr[k] == c; k--) {
                    dp[i][j] = dp[i][j] < dp[k + 1][j] ? dp[i][j] : dp[k + 1][j];
                }
                for (int k = j + 1, c = arr[j]; k <= n && arr[k] == c; k++) {
                    dp[i][j] = dp[i][j] < dp[i][k - 1] ? dp[i][j] : dp[i][k - 1];
                }
            }
            // 如果两端珠子颜色相同且长度大于等于3，则可以消去
            if (arr[i] == arr[j] && len >= 3) {
                dp[i][j]--;
            }
        }
    }

    // 输出最少射出的珠子个数
    printf("%d\n", dp[1][n]);

    return 0;
}