#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000
#define MAX_K 20
#define MAX_VAL 1000000000

int n, k, L, R;
int a[MAX_N + 1];
int dp[MAX_K + 1][MAX_N + 1];
int sum[MAX_N + 1];

// 快速读取输入
int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}

// 比较函数，用于排序
int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

// 计算前缀和
void computePrefixSum() {
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
    }
}

// 计算最大美妙度
int calculateMaxBeauty() {
    // 初始化dp数组
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -MAX_VAL;
        }
    }
    dp[0][0] = 0;

    // 动态规划求解
    for (int i = 1; i <= k; i++) {
        for (int j = L; j <= R; j++) {
            for (int l = j; l <= n; l++) {
                dp[i][l] = dp[i][l] > dp[i - 1][j - 1] + sum[l] - sum[j - 1] ? dp[i][l] : dp[i - 1][j - 1] + sum[l] - sum[j - 1];
            }
        }
    }

    // 找到最大值
    int maxBeauty = -MAX_VAL;
    for (int i = 1; i <= n; i++) {
        maxBeauty = maxBeauty > dp[k][i] ? maxBeauty : dp[k][i];
    }
    return maxBeauty;
}

int main() {
    // 读取输入
    n = read();
    k = read();
    L = read();
    R = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
    }

    // 计算前缀和
    computePrefixSum();

    // 计算最大美妙度
    int maxBeauty = calculateMaxBeauty();

    // 输出结果
    printf("%d\n", maxBeauty);

    return 0;
}