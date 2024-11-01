#include <stdio.h>
#include <string.h>

#define MOD 19901013

int n, m;
char grid[20][20];
int dp[20][20][1 << 16][1 << 16];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }

    // 初始化dp数组
    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0] = 1;

    // 动态规划求解
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int mask1 = 0; mask1 < (1 << m); mask1++) {
                for (int mask2 = 0; mask2 < (1 << m); mask2++) {
                    // 检查当前格子是否有障碍
                    if (grid[i][j] == 'x') {
                        continue;
                    }

                    // 尝试放置1x2的骨牌
                    if (j + 1 < m && grid[i][j + 1] != 'x') {
                        // 检查当前行和下一行的mask是否冲突
                        int new_mask1 = mask1 | (1 << j) | (1 << (j + 1));
                        int new_mask2 = mask2;
                        if ((mask1 & (1 << j)) == 0 && (mask1 & (1 << (j + 1))) == 0) {
                            dp[i][j + 2][new_mask1][new_mask2] = (dp[i][j + 2][new_mask1][new_mask2] + dp[i][j][mask1][mask2]) % MOD;
                        }
                    }

                    // 尝试放置2x1的骨牌
                    if (i + 1 < n && grid[i + 1][j] != 'x') {
                        // 检查当前列和下一列的mask是否冲突
                        int new_mask1 = mask1;
                        int new_mask2 = mask2 | (1 << j) | (1 << (j + 1));
                        if ((mask2 & (1 << j)) == 0 && (mask2 & (1 << (j + 1))) == 0) {
                            dp[i + 2][j][new_mask1][new_mask2] = (dp[i + 2][j][new_mask1][new_mask2] + dp[i][j][mask1][mask2]) % MOD;
                        }
                    }

                    // 不放置骨牌
                    dp[i][j + 1][mask1][mask2] = (dp[i][j + 1][mask1][mask2] + dp[i][j][mask1][mask2]) % MOD;
                }
            }
        }
    }

    // 计算最终结果
    int result = 0;
    for (int mask1 = 0; mask1 < (1 << m); mask1++) {
        for (int mask2 = 0; mask2 < (1 << m); mask2++) {
            if ((mask1 & (1 << (m - 1))) && (mask2 & (1 << (m - 1)))) {
                result = (result + dp[n - 1][m][mask1][mask2]) % MOD;
            }
        }
    }

    printf("%d\n", result);
    return 0;
}