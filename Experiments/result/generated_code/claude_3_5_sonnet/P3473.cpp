#include <stdio.h>
#include <string.h>

#define MAX_N 101
#define MAX_M 101

int n, m, k;
int x, y;
char grid[MAX_N][MAX_M];
int dp[MAX_N][MAX_M][4];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    scanf("%d %d", &x, &y);
    
    for (int i = n; i >= 1; i--) {
        scanf("%s", grid[i] + 1);
    }
    
    dp[n][1][0] = 1;
    
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == '*') continue;
            
            for (int d = 0; d < 4; d++) {
                if (i < n) {
                    dp[i][j][d] = (dp[i][j][d] + dp[i+1][j][d]) % k;
                }
                if (j > 1 && d < 3) {
                    dp[i][j][d+1] = (dp[i][j][d+1] + dp[i][j-1][d]) % k;
                }
            }
        }
    }
    
    int result = 0;
    for (int d = 0; d < 4; d++) {
        result = (result + dp[y][x][d]) % k;
    }
    
    printf("%d\n", result);
    
    return 0;
}