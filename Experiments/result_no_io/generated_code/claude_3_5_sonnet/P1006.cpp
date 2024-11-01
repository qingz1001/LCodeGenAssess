#include <stdio.h>
#include <string.h>

#define MAX_N 50
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int m, n;
int grid[MAX_N][MAX_N];
int dp[MAX_N][MAX_N][MAX_N][MAX_N];

int main() {
    scanf("%d %d", &m, &n);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    
    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                for (int l = 0; l < n; l++) {
                    if (i + j == k + l && i <= k) {
                        int value = (i == k && j == l) ? grid[i][j] : grid[i][j] + grid[k][l];
                        
                        if (i > 0 && k > 0) {
                            dp[i][j][k][l] = MAX(dp[i][j][k][l], dp[i-1][j][k-1][l] + value);
                        }
                        if (i > 0 && l > 0) {
                            dp[i][j][k][l] = MAX(dp[i][j][k][l], dp[i-1][j][k][l-1] + value);
                        }
                        if (j > 0 && k > 0) {
                            dp[i][j][k][l] = MAX(dp[i][j][k][l], dp[i][j-1][k-1][l] + value);
                        }
                        if (j > 0 && l > 0) {
                            dp[i][j][k][l] = MAX(dp[i][j][k][l], dp[i][j-1][k][l-1] + value);
                        }
                    }
                }
            }
        }
    }
    
    printf("%d\n", dp[m-1][n-1][m-1][n-1]);
    
    return 0;
}