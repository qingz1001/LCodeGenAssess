#include <stdio.h>

int N, M;
int land[13][13];
int dp[13][1 << 12];

int main() {
    // 读取输入
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &land[i][j]);
        }
    }

    // 初始化DP数组
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < (1 << M); j++) {
            dp[i][j] = 0;
        }
    }

    // 初始化第一行的状态
    for (int j = 0; j < (1 << M); j++) {
        if ((j & (j << 1)) == 0) { // 检查相邻位置是否有草
            int count = 0;
            for (int k = 0; k < M; k++) {
                if ((j & (1 << k)) && land[0][k]) {
                    count++;
                }
            }
            if (count == __builtin_popcount(j)) { // 检查是否所有选中的位置都是适合种草的
                dp[0][j] = 1;
            }
        }
    }

    // 动态规划填表
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < (1 << M); j++) {
            if ((j & (j << 1)) == 0) { // 检查相邻位置是否有草
                int count = 0;
                for (int k = 0; k < M; k++) {
                    if ((j & (1 << k)) && land[i][k]) {
                        count++;
                    }
                }
                if (count == __builtin_popcount(j)) { // 检查是否所有选中的位置都是适合种草的
                    for (int k = 0; k < (1 << M); k++) {
                        if ((k & (k << 1)) == 0) { // 检查相邻位置是否有草
                            int flag = 1;
                            for (int l = 0; l < M; l++) {
                                if ((j & (1 << l)) && (k & (1 << l))) {
                                    flag = 0;
                                    break;
                                }
                            }
                            if (flag) {
                                dp[i][j] = (dp[i][j] + dp[i-1][k]) % 100000000;
                            }
                        }
                    }
                }
            }
        }
    }

    // 计算结果
    int result = 0;
    for (int j = 0; j < (1 << M); j++) {
        result = (result + dp[N-1][j]) % 100000000;
    }

    // 输出结果
    printf("%d\n", result);
    return 0;
}