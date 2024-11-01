#include <stdio.h>
#include <stdlib.h>

#define MAXN 35005
#define INF 0x3f3f3f3f

int n;
int a[MAXN], b[MAXN], sum[MAXN];
int dp[MAXN], minn[MAXN], minf[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    // 对数组b进行排序
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (b[i] > b[j]) {
                int temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }
        }
    }

    // 计算前缀和
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + b[i];
    }

    // 初始化dp数组
    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
        minn[i] = minf[i] = INF;
    }
    dp[1] = 0;
    minn[1] = minf[1] = 0;

    // 动态规划求解
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i]) {
                dp[i] = dp[i] < dp[j] + 1 ? dp[i] : dp[j] + 1;
                minn[i] = minn[i] < minn[j] + a[i] - a[j] ? minn[i] : minn[j] + a[i] - a[j];
                minf[i] = minf[i] < minf[j] + b[j] - b[i] ? minf[i] : minf[j] + b[j] - b[i];
            }
        }
    }

    // 输出结果
    printf("%d\n%d\n", n - dp[n], minn[n] < minf[n] ? minn[n] : minf[n]);

    return 0;
}