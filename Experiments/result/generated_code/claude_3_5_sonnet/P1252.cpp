#include <stdio.h>
#include <limits.h>

#define N 5
#define M 10

int times[N][M];
int dp[1 << N][26];
int path[1 << N][26];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    // 读取输入数据
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &times[i][j]);
        }
    }

    // 初始化dp数组
    for (int i = 0; i < (1 << N); i++) {
        for (int j = 0; j <= 25; j++) {
            dp[i][j] = INT_MAX;
        }
    }
    dp[0][0] = 0;

    // 动态规划
    for (int mask = 0; mask < (1 << N); mask++) {
        for (int dist = 0; dist < 25; dist++) {
            if (dp[mask][dist] == INT_MAX) continue;
            for (int runner = 0; runner < N; runner++) {
                if (mask & (1 << runner)) continue;
                for (int run = 1; run <= 10 && dist + run <= 25; run++) {
                    int newMask = mask | (1 << runner);
                    int newDist = dist + run;
                    int newTime = dp[mask][dist] + times[runner][run - 1];
                    if (newTime < dp[newMask][newDist]) {
                        dp[newMask][newDist] = newTime;
                        path[newMask][newDist] = (runner << 4) | run;
                    }
                }
            }
        }
    }

    // 输出结果
    printf("%d\n", dp[(1 << N) - 1][25]);

    // 重建路径
    int mask = (1 << N) - 1;
    int dist = 25;
    int result[N] = {0};
    while (mask) {
        int p = path[mask][dist];
        int runner = p >> 4;
        int run = p & 15;
        result[runner] = run;
        mask ^= (1 << runner);
        dist -= run;
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}