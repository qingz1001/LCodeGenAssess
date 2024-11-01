#include <stdio.h>
#include <stdlib.h>

#define MOD 9901

typedef long long ll;

// 动态规划数组，用于存储每个子问题的结果
ll dp[201][101];

// 计算组合数 C(n, k)
ll combination(int n, int k) {
    ll result = 1;
    for (int i = 1; i <= k; ++i) {
        result = result * (n - i + 1) / i;
    }
    return result;
}

// 计算给定节点数 n 和深度 k 的无标号完满二叉树结构数
ll countStructures(int n, int k) {
    // 初始化 dp 数组
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = 0;
        }
    }

    // 基本情况：如果只有一个节点，则只有一种结构
    for (int i = 1; i <= n; ++i) {
        dp[i][1] = 1;
    }

    // 动态规划填表
    for (int j = 2; j <= k; ++j) {
        for (int i = 1; i <= n; ++i) {
            for (int l = 0; l <= i / 2; ++l) {
                dp[i][j] = (dp[i][j] + dp[l][j - 1] * dp[i - 1 - l][j - 1] * combination(i - 1, l)) % MOD;
            }
        }
    }

    return dp[n][k];
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    // 调用函数计算结果并输出
    printf("%lld\n", countStructures(n, k));

    return 0;
}