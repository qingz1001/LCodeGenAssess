#include <stdio.h>
#include <string.h>

#define MAX_N 1001
#define MAX_M 1001
#define INF 0x3f3f3f3f

int n, m, p;
int coins[MAX_N][MAX_M];
int cost[MAX_N];
int dp[MAX_N][MAX_M];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &m, &p);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &coins[i][j]);
        }
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &cost[i]);
    }
    
    memset(dp, -INF, sizeof(dp));
    dp[1][0] = 0;
    
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            int sum = 0;
            for (int k = 1; k <= p && j - k >= 0; k++) {
                sum += coins[i][j - k + 1];
                for (int pre = 1; pre <= n; pre++) {
                    if (pre != i) {
                        dp[i][j] = max(dp[i][j], dp[pre][j - k] + sum - cost[i]);
                    }
                }
            }
        }
    }
    
    int result = -INF;
    for (int i = 1; i <= n; i++) {
        result = max(result, dp[i][m]);
    }
    
    printf("%d\n", result);
    
    return 0;
}