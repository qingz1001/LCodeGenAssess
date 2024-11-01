#include <stdio.h>
#include <stdlib.h>

// 计算花费时间的函数
long long calculate_time(int A, int B, int x) {
    return (long long)A * (1LL << (B * x));
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int A[21], B[21];
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &A[i], &B[i]);
    }

    // dp[i][j] 表示完成前 i 个课题，总共 j 篇论文所需的最少时间
    long long dp[21][201] = {0};

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i-1][j]; // 不选择第 i 个课题
            for (int k = 1; k <= j; k++) {
                dp[i][j] = (dp[i][j] < dp[i-1][j-k] + calculate_time(A[i], B[i], k)) ? dp[i][j] : dp[i-1][j-k] + calculate_time(A[i], B[i], k);
            }
        }
    }

    printf("%lld\n", dp[m][n]);
    return 0;
}