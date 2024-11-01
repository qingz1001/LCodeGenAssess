#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 105

int dp[MAXN][MAXN];
int energy[MAXN];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &energy[i]);
    }

    // 将环形项链展开成链
    for (int i = 0; i < N; i++) {
        energy[N + i] = energy[i];
    }

    // 初始化dp数组
    for (int i = 0; i < 2 * N; i++) {
        for (int j = 0; j < 2 * N; j++) {
            dp[i][j] = 0;
        }
    }

    // 动态规划求解
    for (int len = 2; len <= N; len++) {
        for (int i = 0; i < 2 * N - len + 1; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + energy[i] * energy[k + 1] * energy[j + 1]);
            }
        }
    }

    // 寻找最大值
    int maxEnergy = 0;
    for (int i = 0; i < N; i++) {
        maxEnergy = max(maxEnergy, dp[i][i + N - 1]);
    }

    printf("%d\n", maxEnergy);

    return 0;
}