#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    if (m == 0) {
        printf("1\n");
        return 0;
    }
    
    int dp[n][n];
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    
    for (int k = 1; k <= m; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = 0;
                if ((i + 1) % n != j) dp[i][j] += dp[(i + 1) % n][j];
                if ((i - 1 + n) % n != j) dp[i][j] += dp[(i - 1 + n) % n][j];
            }
        }
    }
    
    printf("%d\n", dp[0][0]);
    return 0;
}