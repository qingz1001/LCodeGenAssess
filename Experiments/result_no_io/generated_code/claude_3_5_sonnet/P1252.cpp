#include <stdio.h>
#include <limits.h>

#define N 5
#define M 10

int time[N][M];
int dp[26][N];
int path[26][N];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    // 读取输入
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &time[i][j]);
        }
    }

    // 初始化dp数组
    for (int i = 0; i <= 25; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = INT_MAX;
        }
    }

    // 动态规划
    for (int j = 0; j < N; j++) {
        for (int i = 1; i <= 10 && i <= 25; i++) {
            dp[i][j] = time[j][i-1];
            path[i][j] = i;
        }
    }

    for (int i = 1; i <= 25; i++) {
        for (int j = 1; j < N; j++) {
            for (int k = 1; k <= 10 && k <= i; k++) {
                if (dp[i-k][j-1] != INT_MAX && dp[i][j] > dp[i-k][j-1] + time[j][k-1]) {
                    dp[i][j] = dp[i-k][j-1] + time[j][k-1];
                    path[i][j] = k;
                }
            }
        }
    }

    // 输出结果
    printf("%d\n", dp[25][N-1]);

    int current = 25;
    int runner[N] = {0};
    for (int i = N-1; i >= 0; i--) {
        runner[i] = path[current][i];
        current -= runner[i];
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", runner[i]);
    }
    printf("\n");

    return 0;
}