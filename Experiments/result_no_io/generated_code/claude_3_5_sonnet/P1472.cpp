#include <stdio.h>
#include <string.h>

#define MOD 9901
#define MAXN 200
#define MAXK 100

int dp[MAXK][MAXN][MAXN];

int solve(int n, int k) {
    memset(dp, 0, sizeof(dp));
    
    // 初始化：深度为1时，只有一个节点
    for (int i = 1; i < MAXN; i++) {
        dp[1][i][i] = 1;
    }
    
    // 动态规划
    for (int d = 2; d <= k; d++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                for (int l = 1; l <= j-1; l++) {
                    dp[d][i][j] = (dp[d][i][j] + dp[d-1][i-j][l] * dp[d-1][j-1][j-1-l]) % MOD;
                }
            }
        }
    }
    
    int result = 0;
    for (int j = 1; j <= n; j++) {
        result = (result + dp[k][n][j]) % MOD;
    }
    
    return result;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    int answer = solve(n, k);
    printf("%d\n", answer);
    
    return 0;
}