#include <stdio.h>

int m, n;
int dp[11][21][1<<20];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int main() {
    scanf("%d%d", &m, &n);
    
    // 初始化dp数组，-1表示未访问
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k < (1 << (m * n)); k++) {
                dp[i][j][k] = -1;
            }
        }
    }
    
    // 初始状态：在左上角，没有访问过任何点
    dp[1][1][1] = 1;
    
    // 动态规划求解
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k < (1 << (m * n)); k++) {
                if (dp[i][j][k] != -1) {
                    for (int d = 0; d < 4; d++) {
                        int ni = i + dx[d];
                        int nj = j + dy[d];
                        if (ni >= 1 && ni <= m && nj >= 1 && nj <= n) {
                            int nk = k | (1 << ((ni - 1) * n + nj - 1));
                            dp[ni][nj][nk] += dp[i][j][k];
                        }
                    }
                }
            }
        }
    }
    
    // 计算最终答案
    int ans = 0;
    for (int k = 0; k < (1 << (m * n)); k++) {
        if (k & 1) {
            ans += dp[m][n][k];
        }
    }
    
    printf("%d\n", ans);
    return 0;
}