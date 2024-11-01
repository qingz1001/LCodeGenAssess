#include <stdio.h>

int main() {
    int n, c;
    scanf("%d %d", &n, &c);

    int position[50], power[50];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &position[i], &power[i]);
    }

    int dp[50][50]; // dp[i][j] 表示从第 i 盏灯到第 j 盏灯关完的最小功耗

    // 初始化 dp 数组
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }

    // 计算每盏灯到另一盏灯的功耗
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                int distance = abs(position[i] - position[j]);
                dp[i][j] = distance * (power[i] + power[j]);
            }
        }
    }

    // 计算从第 i 盏灯到第 j 盏灯关完的最小功耗
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                dp[i][j] = (dp[i][j] < dp[i][k] + dp[k + 1][j]) ? dp[i][j] : dp[i][k] + dp[k + 1][j];
            }
        }
    }

    // 计算从老张所在位置开始关灯的最小功耗
    int min_power = dp[c - 1][n - 1];
    for (int i = 0; i < c - 1; i++) {
        for (int j = c - 1; j < n; j++) {
            int distance = abs(position[i] - position[c - 1]) + abs(position[j] - position[c - 1]);
            min_power = (min_power < distance * (power[i] + power[j]) + dp[i][j]) ? min_power : distance * (power[i] + power[j]) + dp[i][j];
        }
    }

    printf("%d\n", min_power);
    return 0;
}