#include <stdio.h>
#include <string.h>

int n, m, v, k;
int price[61], recycle[61];
int magic[241][61], magic_count[241];
int dp[1001][31];

int main() {
    // 读取输入
    scanf("%d %d %d %d", &n, &m, &v, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &price[i], &recycle[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &magic[i][0], &magic_count[i]);
        for (int j = 1; j <= magic_count[i]; j++) {
            scanf("%d", &magic[i][j]);
        }
    }

    // 初始化dp数组
    memset(dp, 0, sizeof(dp));

    // 动态规划求解
    for (int i = 1; i <= m; i++) { // 遍历每种魔法
        for (int j = v; j >= price[magic[i][0]]; j--) { // 遍历当前的钱数
            for (int l = 1; l <= k; l++) { // 遍历当前使用的魔法次数
                int cost = 0;
                for (int t = 1; t <= magic_count[i]; t++) { // 计算合成所需的成本
                    cost += recycle[magic[i][t]];
                }
                if (j >= cost && l > 0) { // 判断是否有足够的钱和魔法次数
                    dp[j][l] = (dp[j][l] > dp[j - cost][l - 1] + price[magic[i][0]] - cost) ? dp[j][l] : dp[j - cost][l - 1] + price[magic[i][0]] - cost;
                }
            }
        }
    }

    // 输出结果
    printf("%d\n", dp[v][k]);

    return 0;
}