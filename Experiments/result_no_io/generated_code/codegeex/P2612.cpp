#include <stdio.h>
#include <math.h>

#define MAXN 110
#define MAXM 2147483647

int N, M, K;
double dp[MAXN][MAXM];

void solve() {
    // 输入
    scanf("%d %d %d", &N, &M, &K);

    // 初始化dp数组
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;

    // 动态规划
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= M; j++) {
            if (dp[i][j] > 0) {
                for (int k = 1; k <= N; k++) {
                    int diff = abs(k - i);
                    if (j + diff <= M) {
                        dp[i + 1][j + diff] += dp[i][j];
                    }
                }
            }
        }
    }

    // 计算概率
    double total = pow(N, N);
    double result = 0;
    for (int j = M; j <= M; j++) {
        result += dp[N][j];
    }

    // 输出结果
    printf("%.5f\n", result / total);
}

int main() {
    solve();
    return 0;
}