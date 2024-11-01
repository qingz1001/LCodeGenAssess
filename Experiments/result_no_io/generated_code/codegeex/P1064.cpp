#include <stdio.h>
#include <string.h>

#define MAX_N 32000
#define MAX_M 60
#define MAX_ITEMS 100

int v[MAX_ITEMS], p[MAX_ITEMS], q[MAX_ITEMS], w[MAX_ITEMS];
int dp[MAX_N / 10 + 1][MAX_ITEMS];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    n /= 10; // 将价格转换为以10为单位

    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &v[i], &p[i], &q[i]);
        w[i] = v[i] * p[i]; // 计算价格与重要度的乘积
    }

    for (int i = 1; i <= m; i++) {
        if (q[i] == 0) { // 主件
            for (int j = n; j >= v[i]; j--) {
                for (int k = 0; k <= j - v[i]; k++) {
                    dp[j][i] = (dp[j][i] > dp[j - k - v[i]][0] + k * w[i]) ? dp[j][i] : dp[j - k - v[i]][0] + k * w[i];
                }
            }
        } else { // 附件
            for (int j = n; j >= v[i]; j--) {
                for (int k = 0; k <= j - v[i]; k++) {
                    dp[j][i] = (dp[j][i] > dp[j - k - v[i]][q[i]] + k * w[i]) ? dp[j][i] : dp[j - k - v[i]][q[i]] + k * w[i];
                }
            }
        }
    }

    printf("%d\n", dp[n][0]); // 输出结果
    return 0;
}