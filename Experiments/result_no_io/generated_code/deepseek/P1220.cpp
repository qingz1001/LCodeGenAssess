#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 50
#define INF INT_MAX

typedef struct {
    int position;
    int power;
} Light;

int n, c;
Light lights[MAXN];
int dp[MAXN][MAXN][2];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d %d", &n, &c);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &lights[i].position, &lights[i].power);
    }

    // 计算总功率
    int total_power = 0;
    for (int i = 0; i < n; i++) {
        total_power += lights[i].power;
    }

    // 初始化dp数组
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j][0] = dp[i][j][1] = INF;
        }
    }

    // 初始位置的功耗
    dp[c - 1][c - 1][0] = dp[c - 1][c - 1][1] = 0;

    // 动态规划
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            if (i > 0) {
                dp[i - 1][j][0] = min(dp[i - 1][j][0], dp[i][j][0] + (lights[i].position - lights[i - 1].position) * (total_power - (lights[i].power + lights[j].power)));
                dp[i - 1][j][0] = min(dp[i - 1][j][0], dp[i][j][1] + (lights[j].position - lights[i - 1].position) * (total_power - (lights[i].power + lights[j].power)));
            }
            if (j < n - 1) {
                dp[i][j + 1][1] = min(dp[i][j + 1][1], dp[i][j][0] + (lights[j + 1].position - lights[i].position) * (total_power - (lights[i].power + lights[j].power)));
                dp[i][j + 1][1] = min(dp[i][j + 1][1], dp[i][j][1] + (lights[j + 1].position - lights[j].position) * (total_power - (lights[i].power + lights[j].power)));
            }
        }
    }

    // 计算最小功耗
    int result = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result = min(result, dp[i][j][0]);
            result = min(result, dp[i][j][1]);
        }
    }

    printf("%d\n", result);
    return 0;
}