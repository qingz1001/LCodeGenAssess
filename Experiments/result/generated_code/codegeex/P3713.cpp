#include <stdio.h>
#include <string.h>

#define MOD 1000000009

int m, n;
char grid[31][31];
int dp[31][31][31][31];

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++) {
        scanf("%s", grid[i] + 1);
    }

    // 初始化dp数组
    memset(dp, 0, sizeof(dp));

    // 计算所有机动路径的权重之和
    for (int x1 = 1; x1 <= m; x1++) {
        for (int y1 = 1; y1 <= n; y1++) {
            for (int x2 = 1; x2 <= m; x2++) {
                for (int y2 = 1; y2 <= n; y2++) {
                    if (x1 != x2 || y1 != y2) {
                        // 判断是否为机动路径
                        if ((x1 == x2 && abs(y1 - y2) <= 1) || (y1 == y2 && abs(x1 - x2) <= 1)) {
                            dp[x1][y1][x2][y2] = 1;
                        }
                    }
                }
            }
        }
    }

    // 计算路径权重
    for (int x1 = 1; x1 <= m; x1++) {
        for (int y1 = 1; y1 <= n; y1++) {
            for (int x2 = 1; x2 <= m; x2++) {
                for (int y2 = 1; y2 <= n; y2++) {
                    if (dp[x1][y1][x2][y2] == 1) {
                        int weight = 1;
                        // 统计相同地形序列的路径数量
                        for (int x3 = 1; x3 <= m; x3++) {
                            for (int y3 = 1; y3 <= n; y3++) {
                                if (grid[x1][y1] == grid[x2][y2] && grid[x2][y2] == grid[x3][y3]) {
                                    weight++;
                                }
                            }
                        }
                        dp[x1][y1][x2][y2] = weight;
                    }
                }
            }
        }
    }

    // 计算所有机动路径的权重之和
    int result = 0;
    for (int x1 = 1; x1 <= m; x1++) {
        for (int y1 = 1; y1 <= n; y1++) {
            for (int x2 = 1; x2 <= m; x2++) {
                for (int y2 = 1; y2 <= n; y2++) {
                    result = (result + dp[x1][y1][x2][y2]) % MOD;
                }
            }
        }
    }

    printf("%d\n", result);
    return 0;
}