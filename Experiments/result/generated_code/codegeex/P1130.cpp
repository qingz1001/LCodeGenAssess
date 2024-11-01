#include <stdio.h>
#include <limits.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    int group[M][N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &group[i][j]);
        }
    }

    // dp[i][j] 表示在第 i 步，选择第 j 组所需的最少天数
    int dp[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0) {
                // 第一步，直接选择当前组
                dp[i][j] = group[j][i];
            } else if (j == 0) {
                // 当前组是第一个组，可以从前一步的最后一个组转移过来
                dp[i][j] = dp[i-1][M-1] + group[j][i];
            } else if (j == M-1) {
                // 当前组是最后一个组，可以从前一步的第一个组转移过来
                dp[i][j] = dp[i-1][0] + group[j][i];
            } else {
                // 其他情况，可以从前一步的相邻组转移过来
                dp[i][j] = dp[i-1][j-1] + group[j][i];
            }
        }
    }

    // 找到最后一行中的最小值
    int min_days = INT_MAX;
    for (int j = 0; j < M; j++) {
        if (dp[N-1][j] < min_days) {
            min_days = dp[N-1][j];
        }
    }

    printf("%d\n", min_days);
    return 0;
}