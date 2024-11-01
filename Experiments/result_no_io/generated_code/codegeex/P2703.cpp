#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);

    int L[1000001], R[1000001];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &L[i], &R[i]);
    }

    int dp[1000001][2] = {0};
    int ans = 0;

    // 初始化dp数组
    for (int i = 0; i <= n; i++) {
        dp[i][0] = dp[i][1] = 0x7fffffff; // 0x7fffffff表示无穷大
    }

    dp[0][0] = 0; // 起始状态，没有腐蚀，代价为0

    // 动态规划求解最小代价
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            // 如果腐蚀第i行
            if (dp[j][0] != 0x7fffffff && dp[j][0] + (i - j) * 2 <= dp[i + 1][1]) {
                dp[i + 1][1] = dp[j][0] + (i - j) * 2;
            }
            // 如果不腐蚀第i行
            if (dp[j][1] != 0x7fffffff && dp[j][1] + (i - j) * 2 <= dp[i + 1][0]) {
                dp[i + 1][0] = dp[j][1] + (i - j) * 2;
            }
        }
    }

    ans = dp[n][0] < dp[n][1] ? dp[n][0] : dp[n][1];

    printf("%d\n", ans);

    return 0;
}