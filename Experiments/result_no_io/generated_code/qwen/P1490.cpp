#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int minCoins(int n) {
    int coins[MAXN];
    for (int i = 1; i <= n; ++i) {
        coins[i] = i;
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j * i <= n; ++j) {
            if (coins[j * i] > coins[j - 1] + i) {
                coins[j * i] = coins[j - 1] + i;
            }
        }
    }
    return coins[n];
}

int countWays(int n) {
    int dp[MAXN][MAXN];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j >= i) {
                dp[i][j] += dp[i - 1][j - i];
            }
        }
    }
    return dp[n][n];
}

int main() {
    int n;
    scanf("%d", &n);
    int minNum = minCoins(n);
    int ways = countWays(minNum);
    printf("%d %d\n", minNum, ways);
    return 0;
}