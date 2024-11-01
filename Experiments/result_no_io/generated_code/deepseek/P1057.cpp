#include <stdio.h>

#define MAXN 31
#define MAXM 31

int dp[MAXM][MAXN];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    dp[0][0] = 1; // 初始状态，球在小蛮手里

    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = dp[i-1][(j-1+n)%n] + dp[i-1][(j+1)%n];
        }
    }

    printf("%d\n", dp[m][0]);

    return 0;
}