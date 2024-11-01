#include <stdio.h>

int main() {
    int n, m, x, y;
    scanf("%d %d %d %d", &n, &m, &x, &y);
    
    if (x == 0 && y == 0) {
        printf("0\n");
        return 0;
    }
    
    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = 0;
        }
    }
    
    dp[0][0] = 1;
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i > 0) {
                dp[i][j] += dp[i - 1][j];
            }
            if (j > 0) {
                dp[i][j] += dp[i][j - 1];
            }
        }
    }
    
    if (x == 1 && y == 2 || x == 2 && y == 1) {
        dp[x][y] -= 1;
    }
    
    printf("%d\n", dp[n][m]);
    
    return 0;
}