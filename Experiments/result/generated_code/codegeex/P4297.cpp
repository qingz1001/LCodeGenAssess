#include <stdio.h>
#include <string.h>

#define N 1024
#define INF 0x3f3f3f3f

int n, a[N], c[N], f[N][N];
int dp[2][N][2];

int main() {
    scanf("%d", &n);
    int sz = 1 << n;
    for (int i = 1; i <= sz; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= sz; i++) scanf("%d", &c[i]);
    for (int i = 1; i <= sz; i++) {
        for (int j = i + 1; j <= sz; j++) {
            scanf("%d", &f[i][j]);
            f[j][i] = f[i][j];
        }
    }

    // 初始化dp数组
    memset(dp, INF, sizeof(dp));
    dp[0][1][a[1]] = 0;
    dp[1][1][1 - a[1]] = 0;

    // 动态规划求解最小费用
    for (int i = 2; i <= sz; i++) {
        for (int j = 1; j < i; j++) {
            dp[i & 1][j][0] = dp[(i & 1) ^ 1][j][0] + c[i];
            dp[i & 1][j][1] = dp[(i & 1) ^ 1][j][1] + c[i];
            if (a[i]) {
                dp[i & 1][j][0] = dp[(i & 1) ^ 1][j][0];
                dp[i & 1][j][1] = dp[(i & 1) ^ 1][j][1] + c[i];
            } else {
                dp[i & 1][j][0] = dp[(i & 1) ^ 1][j][0] + c[i];
                dp[i & 1][j][1] = dp[(i & 1) ^ 1][j][1];
            }
        }
        for (int j = 1; j < i; j++) {
            dp[i & 1][i][0] = dp[(i & 1) ^ 1][j][0] + f[j][i];
            dp[i & 1][i][1] = dp[(i & 1) ^ 1][j][1] + f[j][i];
            if (a[i]) {
                dp[i & 1][i][0] = dp[(i & 1) ^ 1][j][0];
                dp[i & 1][i][1] = dp[(i & 1) ^ 1][j][1] + f[j][i];
            } else {
                dp[i & 1][i][0] = dp[(i & 1) ^ 1][j][0] + f[j][i];
                dp[i & 1][i][1] = dp[(i & 1) ^ 1][j][1];
            }
        }
    }

    // 找到最小费用
    int ans = INF;
    for (int i = 1; i <= sz; i++) {
        ans = ans < dp[sz & 1][i][0] ? ans : dp[sz & 1][i][0];
        ans = ans < dp[sz & 1][i][1] ? ans : dp[sz & 1][i][1];
    }

    printf("%d\n", ans);
    return 0;
}